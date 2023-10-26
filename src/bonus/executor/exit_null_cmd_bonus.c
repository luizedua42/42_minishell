/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_null_cmd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:04:34 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/26 01:00:33 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	exit_null_cmd(int *pipedes)
{
	clear_shell(getset_mini(NULL));
	close_sysfd(0);
	close_pipedes(pipedes);
	return (EXIT_SUCCESS);
}
