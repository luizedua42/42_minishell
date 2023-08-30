/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:32:25 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 11:57:31 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	slen;

	slen = ft_strlen(little);
	if (slen == 0)
		return ((char *)big);
	while (*big && slen <= len)
	{
		if (ft_memcmp(big, little, slen) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (0);
}
