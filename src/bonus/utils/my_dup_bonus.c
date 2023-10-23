/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:34:11 by paulo             #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	my_dup(int fd, int fd2)
{
	dup2(fd, fd2);
	close(fd);
}