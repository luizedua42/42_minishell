/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:26:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/09 22:07:43 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_redirect(t_minishell *minishell, char *redirect_to);

int	open_file(t_minishell *minishell, t_fd *fd)
{
	int		ret;
	char	*error_message;

	if (fd->type == REDIRECT_IN)
	{
		fd->redirect_to = expand_redirect(minishell, fd->redirect_to);
		ret = open(fd->redirect_to, O_RDONLY);
	}
	else if (fd->type == REDIRECT_OUT)
	{
		fd->redirect_to = expand_redirect(minishell, fd->redirect_to);
		ret = open(fd->redirect_to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		fd->redirect_to = expand_redirect(minishell, fd->redirect_to);
		ret = open(fd->redirect_to, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (ret == -1)
	{
		error_message = ft_strjoin("minishell: ", fd->redirect_to);
		perror(error_message);
		free(error_message);
		exit(errno);
	}
	return (ret);
}

static char *expand_redirect(t_minishell *minishell, char *redirect_to)
{
	char	*expand;

	expand = expand(minishell, redirect_to, false);
	free(redirect_to);
	return (expand);
}
