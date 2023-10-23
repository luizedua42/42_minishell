/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:40:56 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
		if (!open_file(minishell, file))
		{
			close_fds(head);
			ft_lstclear(&head, del_fd);
			if (!has_pipe)
			{
				minishell->exit_status = EXIT_FAILURE;
				return (false);
			}
			free_token_array(token_array);
			clear_shell(minishell);
			exit(EXIT_FAILURE);
		}
		fds = fds->next;
	}
	return (true);
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
