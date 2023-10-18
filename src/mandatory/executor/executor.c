/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:27:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/18 21:25:54 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_list *fds)
{
	t_fd	*file;

	while(fds != NULL)
	{
		file = fds->content;
		if (file->fd == -1)
			break;
		close(file->fd);
		fds = fds->next;
	}
}

void	open_redirects(t_minishell *minishell, t_list *fds)
{
	t_fd	*file;

	while (fds != NULL)
	{
		file = fds->content;
		open_file(minishell, file);
		fds = fds->next;
	}
}

int	executor(t_minishell *minishell)
{
	size_t	i;
	t_list	**token_array;
	size_t	lst_size;

	open_redirects(minishell, minishell->fds);
	expand_all(minishell, minishell->tokens);
	token_array = split_pipes(minishell->tokens);
	lst_size = lst_matrix_len(token_array);
	minishell->pids = ft_calloc(lst_size, sizeof(int));
	i = -1;
	while (token_array[++i] != NULL)
		minishell->pids[i] = do_pipe(minishell, token_array[i], i, token_array);
	i = 0;
	while (i < lst_size)
		waitpid(minishell->pids[i++], NULL, 0);
	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
	close_fds(minishell->fds);
	return (errno);
}
