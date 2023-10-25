/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:38:57 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/25 20:40:05 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*getset_filename(char *file_name)
{
	static char	*file;

	if (file_name != NULL)
		file = file_name;
	return (file);
}

int	getset_fd(int fd)
{
	static int	fd_static;

	if (fd != -1)
		fd_static = fd;
	return (fd_static);
}

t_minishell	*getset_mini_here(t_minishell *minishell)
{
	static t_minishell	*mini;

	if (minishell != NULL)
		mini = minishell;
	return (mini);
}

t_minishell	*getset_mini(t_minishell *minishell)
{
	static t_minishell	*mini;

	if (minishell != NULL)
		mini = minishell;
	return (mini);
}
