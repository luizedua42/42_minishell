/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:40:56 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/18 22:04:42 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	*match_fd(t_fd *file, t_list *parent_files);

bool	analyse_fds(t_list *child_files, t_list *parent_files)
{
	t_fd	*file;
	t_fd	*match;

	while (child_files != NULL)
	{
		file = child_files->content;
		match = match_fd(file, parent_files);
		if (match->fd == -2)
			return (false);
		child_files = child_files->next;
	}
	return (true);
}

static	t_fd	*match_fd(t_fd *file, t_list *parent_files)
{
	t_fd	*p_file;

	while (parent_files != NULL)
	{
		p_file = parent_files->content;
		if (file->type == p_file->type && \
			ft_strcmp(file->redirect_to, p_file->redirect_to) == 0)
			return (p_file);
		parent_files = parent_files->next;
	}
	return (p_file);
}

int	get_last_fd(int type, t_list *fds)
{
	t_fd	*file;
	int		last_fd;

	last_fd = -2;
	while (fds != NULL)
	{
		file = fds->content;
		if (type == STDIN_FILENO && file->type == REDIRECT_IN)
			last_fd = file->fd;
		if (type  == STDOUT_FILENO && \
			(file->type == REDIRECT_OUT || file->type == HEREDOC_OUT))
			last_fd = file->fd;
		fds = fds->next;
	}
	return (last_fd);
}