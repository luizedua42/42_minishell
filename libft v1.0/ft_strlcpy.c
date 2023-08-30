/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:26:26 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 12:41:55 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	sized;
	size_t	sizes;

	sized = 0;
	sizes = 0;
	while (src[sizes])
		sizes++;
	if (size != '\0')
	{
		while (sized < size - 1 && src[sized] != '\0')
		{
			dst[sized] = src[sized];
			sized++;
		}
		dst[sized] = '\0';
	}
	return (sizes);
}
