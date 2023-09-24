/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:48:55 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/23 02:26:16 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
