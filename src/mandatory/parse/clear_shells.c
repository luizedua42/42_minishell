/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:06:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/18 21:26:47 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	ft_lstclear(&((t_minishell *)minishell)->envs, del_env);
	((t_minishell *)minishell)->envs = NULL;
	ft_lstclear(&((t_minishell *)minishell)->fds, del_fd);
	((t_minishell *)minishell)->fds = NULL;
	if (((t_minishell *)minishell)->pids != NULL)
	{
		free(((t_minishell *)minishell)->pids);
		((t_minishell *)minishell)->pids = NULL;
	}
	ft_lstclear(&((t_minishell *)minishell)->shells, clear_shell);
	((t_minishell *)minishell)->shells = NULL;
	free(minishell);
	close_fds(((t_minishell *)minishell)->fds);
}

void	clear_subshells(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	ft_lstclear(&((t_minishell *)minishell)->fds, del_fd);
	((t_minishell *)minishell)->fds = NULL;
	if (((t_minishell *)minishell)->pids != NULL)
	{
		free(((t_minishell *)minishell)->pids);
		((t_minishell *)minishell)->pids = NULL;
	}
	ft_lstclear(&((t_minishell *)minishell)->shells, clear_shell);
	((t_minishell *)minishell)->shells = NULL;
}
