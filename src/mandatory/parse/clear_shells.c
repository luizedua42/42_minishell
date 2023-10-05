/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_shells.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:06:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/04 20:56:18 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shells(void *minishell)
{
	ft_lstclear(&((t_minishell *)minishell)->tokens, del_token);
	((t_minishell *)minishell)->tokens = NULL;
	ft_lstclear(&((t_minishell *)minishell)->envs, del_env);
	((t_minishell *)minishell)->envs = NULL;
	ft_lstclear(&((t_minishell *)minishell)->shells, clear_shells);
	((t_minishell *)minishell)->shells = NULL;
	clear_fds(((t_minishell *)minishell));
	free(minishell);
}
