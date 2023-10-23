/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 03:25:38 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	builtin_exit(char **cmds, t_list **token_array, int ret, \
					t_minishell *minishell)
{
	size_t	i;

	if (ft_strncmp(cmds[0], "exit", 5) == 0)
	{
		if (ret != -2)
		{
			free(cmds);
			i = -1;
			while (token_array[++i] != NULL)
				ft_lstclear(&token_array[i], del_token);
			free(token_array);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			exit(ret);
		}
		else
		{
			free(cmds);
			minishell->exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

t_bfd	builtin_fds(t_list *child_files)
{
	t_bfd	builtin_fd;

	builtin_fd.last_fdin = get_last_fd(STDIN_FILENO, child_files, -1);
	if (builtin_fd.last_fdin != -1)
	{
		builtin_fd.safe_in = dup(STDIN_FILENO);
		my_dup(builtin_fd.last_fdin, STDIN_FILENO);
	}
	builtin_fd.last_fdout = get_last_fd(STDOUT_FILENO, child_files, -1);
	if (builtin_fd.last_fdout != -1)
	{
		builtin_fd.safe_out = dup(STDOUT_FILENO);
		my_dup(builtin_fd.last_fdout, STDOUT_FILENO);
	}
	ft_lstclear(&child_files, del_fd);
	return (builtin_fd);
}
