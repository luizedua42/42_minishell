/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:06:21 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 12:41:44 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	si;
	size_t	ldst;
	size_t	lsrc;

	si = 0;
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (size < ldst)
		return (size + lsrc);
	while (*(src + si) && si + 1 < (size - ldst))
	{
		*(dst + ldst + si) = *(src + si);
		si++;
	}
	*(dst + ldst + si) = '\0';
	return (ldst + lsrc);
}
