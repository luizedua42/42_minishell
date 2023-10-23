/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:27:55 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	pipe_validation(bool is_last, int *pipedes, int hostage_pipe)
{
	pipedes[2] = hostage_pipe;
	if (!is_last && pipe(pipedes) == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}

int	fork_validation(int *pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	return (0);
}
