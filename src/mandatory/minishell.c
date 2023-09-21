/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/09/20 21:29:48 by pdavi-al         ###   ########.fr       */
=======
/*   Updated: 2023/09/20 21:35:18 by luizedua         ###   ########.fr       */
>>>>>>> starting parser
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
	t_tree	*tree;
	t_list	*tokens;
	char	*command;
	char	*prompt;
	t_list	*envs;

	(void)argc;
	(void)argv;
	envs = create_envs(envp);
	while (1)
	{
		prompt = "\001\x1b[32m\002minishell$ \001\x1b[0m\002";
		command = readline(prompt);
		if (command[0] == '[')
			break ;
		tokens = create_tokens(command);
		if(syntax_analyzer(tokens) == false)
		{
			ft_lstclear(&tokens, del_token);
			free(command);
			break ;
		}
		print_tokens(tokens);
		ft_lstclear(&tokens, del_token);
		ft_cleantree(tree, del_token);
		free(command);
	}
	free(command);
	print_envs(envs);
	ft_lstclear(&envs, del_env);
	return (0);
}
