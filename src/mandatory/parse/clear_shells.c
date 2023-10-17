/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:06:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/16 23:36:55 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	ft_lstclear(&((t_minishell *)minishell)->envs, del_env);
	((t_minishell *)minishell)->envs = NULL;
	clear_fds(((t_minishell *)minishell));
	if (((t_minishell *)minishell)->pids != NULL)
	{
		free(((t_minishell *)minishell)->pids);
		((t_minishell *)minishell)->pids = NULL;
	}
	ft_lstclear(&((t_minishell *)minishell)->shells, clear_shell);
	((t_minishell *)minishell)->shells = NULL;
	free(minishell);
}

void	clear_subshells(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	clear_fds(((t_minishell *)minishell));
	if (((t_minishell *)minishell)->pids != NULL)
	{
		free(((t_minishell *)minishell)->pids);
		((t_minishell *)minishell)->pids = NULL;
	}
	ft_lstclear(&((t_minishell *)minishell)->shells, clear_shell);
	((t_minishell *)minishell)->shells = NULL;
}
