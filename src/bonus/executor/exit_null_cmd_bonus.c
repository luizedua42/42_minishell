/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_null_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:04:34 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/25 22:05:53 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	exit_null_cmd(t_minishell *minishell, int *pipedes)
{
	clear_shell(minishell);
	close_sysfd(0);
	close_pipedes(pipedes);
	return (EXIT_SUCCESS);
}
