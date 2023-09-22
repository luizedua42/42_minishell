/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/21 21:55:50 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(void *content)
{
	t_env	*env;

	env = content;
	free(env->key);
	free(env->value);
	free(env);
}

void	del_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

void	print_tokens(t_list *tokens)
{
	t_token	*aux;

	while (tokens != NULL)
	{
		aux = tokens->content;
		ft_printf("value: %s	type : %i\n", aux->value, aux->type);
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list			*tokens;
	char			*command;
	char			*prompt;
	t_list			*envs;
	t_token_type	*token_array;
	int				i;

	cd(argv);
	return (0);
	i = 0;
	(void)argc;
	(void)argv;
	envs = create_envs(envp);
	while (1)
	{
		i = 0;
		prompt = "\001\x1b[32m\002minishell$ \001\x1b[0m\002";
		command = readline(prompt);
		add_history(command);
		if (command[0] == '[')
			break ;
		tokens = create_tokens(command);
		token_array = create_token_array(tokens, &i);
		if (syntax_analysis(token_array) == false)
			ft_fprintf(2, "minishell : syntax error\n");
		else
			print_tokens(tokens);
		free(token_array);
		ft_lstclear(&tokens, del_token);
		free(command);
	}
	rl_clear_history();
	free(command);
	ft_lstclear(&envs, del_env);
	return (0);
}
