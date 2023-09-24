/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:57:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/23 23:46:47 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_exit(t_minishell *minishell)
{
	rl_clear_history();
	if (minishell->tokens != NULL)
		ft_lstclear(&minishell->tokens, del_token);
	if (minishell->envs != NULL)
		ft_lstclear(&minishell->envs, del_env);
	return (EXIT_SUCCESS);
}

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
