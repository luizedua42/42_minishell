/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:34:42 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 12:44:57 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*desttemp;
	unsigned char	*srctemp;
	size_t			i;

	i = 0;
	desttemp = (unsigned char *)dest;
	srctemp = (unsigned char *)src;
	while (i < n)
	{
		desttemp[i] = srctemp[i];
		i++;
	}
	return (dest);
}
