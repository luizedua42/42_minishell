/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:57:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 12:41:32 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_exit(t_minishell *minishell)
{
	rl_clear_history();
	if (minishell->tokens != NULL)
		ft_lstclear(&minishell->tokens, del_token);
	if (minishell->envs != NULL)
		ft_lstclear(&minishell->envs, del_env);
	clear_fds(minishell);
	return (EXIT_SUCCESS);
}
