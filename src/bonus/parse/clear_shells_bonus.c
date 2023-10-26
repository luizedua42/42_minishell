/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shells_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:06:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	clear_shell(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	ft_lstclear(&((t_minishell *)minishell)->envs, del_env);
	((t_minishell *)minishell)->envs = NULL;
	if (((t_minishell *)minishell)->pids != NULL)
	{
		free(((t_minishell *)minishell)->pids);
		((t_minishell *)minishell)->pids = NULL;
	}
	free(minishell);
}

void	clear_shell_content(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	if (((t_minishell *)minishell)->pids != NULL)
	{
		free(((t_minishell *)minishell)->pids);
		((t_minishell *)minishell)->pids = NULL;
	}
}
