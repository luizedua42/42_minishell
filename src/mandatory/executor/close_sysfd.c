/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_sysfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:13:58 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/24 16:15:17 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_sysfd(int ret)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (ret);
}
