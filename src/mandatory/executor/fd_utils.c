/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:40:56 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/24 16:02:58 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_list *fds)
{
	t_fd	*file;

	while (fds != NULL)
	{
		file = fds->content;
		if (file->fd != -1)
			close(file->fd);
		fds = fds->next;
	}
}

bool	open_redirects(t_minishell *minishell, t_list *fds,
		t_list **token_array, bool has_pipe)
{
	t_fd	*file;
	t_list	*head;

	head = fds;
	while (fds != NULL)
	{
		file = fds->content;
		if (!open_file(file))
		{
			close_fds(head);
			ft_lstclear(&head, del_fd);
			minishell->exit_status = -EXIT_FAILURE;
			if (!has_pipe)
				return (false);
			free_token_array(token_array);
			clear_shell(minishell);
			return (false);
		}
		fds = fds->next;
	}
	return (true);
}

int	close_pipedes(int *pipedes)
{
	close(pipedes[0]);
	close(pipedes[1]);
	close(pipedes[2]);
	return (EXIT_FAILURE);
}

int	get_last_fd(int type, t_list *fds, int default_fd)
{
	t_fd	*file;
	int		last_fd;

	last_fd = default_fd;
	while (fds != NULL)
	{
		file = fds->content;
		if (type == STDIN_FILENO && (file->type == REDIRECT_IN
				|| file->type == HEREDOC_IN))
			last_fd = file->fd;
		if (type == STDOUT_FILENO && (file->type == REDIRECT_OUT
				|| file->type == HEREDOC_OUT))
			last_fd = file->fd;
		fds = fds->next;
	}
	return (last_fd);
}
