/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:48:55 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

size_t	count_args(char **args)
{
	size_t	size;

	size = 0;
	if (args == NULL)
		return (0);
	while (*args != NULL)
	{
		args++;
		size++;
	}
	return (size);
}
