/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:48:55 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 22:17:53 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_args(char **args)
{
	size_t	size;

	size = 0;
	while (*args != NULL)
	{
		args++;
		size++;
	}
	return (size);
}
