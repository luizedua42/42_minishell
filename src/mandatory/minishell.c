/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/21 20:50:16 by luizedua         ###   ########.fr       */
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

void	print_envs(t_list *envs)
{
	t_env	*env;

	while (envs != NULL)
	{
		env = envs->content;
		ft_printf("key: %s | value: %s\n", env->key, env->value);
		envs = envs->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*tokens;
	char	*command;
	char	*prompt;
	t_list	*envs;
	int		*token_array;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	envs = create_envs(envp);
	while (1)
	{
		i = 0;
		prompt = "\001\x1b[32m\002minishell$ \001\x1b[0m\002";
		command = readline(prompt);
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
	free(token_array);
	free(command);
	print_envs(envs);
	ft_lstclear(&envs, del_env);
	return (0);
}
