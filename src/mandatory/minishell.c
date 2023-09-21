/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/20 21:29:48 by pdavi-al         ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	envs = create_envs(envp);
	while (1)
	{
		prompt = "minishell$ ";
		command = readline(prompt);
		if (command[0] == '[')
			break ;
		tokens = create_tokens(command);
		print_tokens(tokens);
		ft_lstclear(&tokens, del_token);
		free(command);
	}
	free(command);
	print_envs(envs);
	ft_lstclear(&envs, del_env);
	return (0);
}
