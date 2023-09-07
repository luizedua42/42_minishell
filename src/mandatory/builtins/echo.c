/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 20:26:19 by luizedua          #+#    #+#             */
/*   Updated: 2023/08/30 20:30:24 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void echo_built(char *str, int n)
{
	if (n == 1)
	{
		ft_putstr_fd(str, 1);
	}
	else
		ft_putendl_fd(str, 1);
}

int main()
{
	echo_built("tes\nte\n", 0);
	echo_built("tes\nte\n", 1);
}