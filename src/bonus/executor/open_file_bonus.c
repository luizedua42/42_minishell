/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:26:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/25 16:37:55 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static bool	handler_error(char *redirect_to);

bool	open_file(t_fd *file)
{
	int	fd;

	if (file->type == REDIRECT_IN || file->type == HEREDOC_IN)
		fd = open(file->redirect_to, O_RDONLY);
	else if (file->type == REDIRECT_OUT)
		fd = open(file->redirect_to, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file->redirect_to, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		file->fd = -2;
		return (handler_error(file->redirect_to));
	}
	file->fd = fd;
	return (true);
}

static bool	handler_error(char *redirect_to)
{
	char	*error_message;

	error_message = ft_strjoin("minishell: ", redirect_to);
	perror(error_message);
	free(error_message);
	return (false);
}
