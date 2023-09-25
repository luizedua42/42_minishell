/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:25:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 12:43:03 by pdavi-al         ###   ########.fr       */
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

void	clear_fds(t_minishell *minishell)
{
	minishell->fds.fd_in.type = END_ARRAY;
	del_fd(&minishell->fds.fd_in);
	minishell->fds.fd_out.type = END_ARRAY;
	del_fd(&minishell->fds.fd_out);
	minishell->fds.fd_error.type = END_ARRAY;
	del_fd(&minishell->fds.fd_error);
}

void	del_fd(t_fd *fd)
{
	if (fd->redirect_to != NULL)
	{
		free(fd->redirect_to);
		fd->redirect_to = NULL;
	}
}

void	del_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}
