/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:47:07 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 12:44:44 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1temp;
	unsigned char	*s2temp;
	size_t			i;

	i = 0;
	s1temp = (unsigned char *)s1;
	s2temp = (unsigned char *)s2;
	while (i < n)
	{
		if (s1temp[i] == s2temp[i])
			i++;
		else
			return (s1temp[i] - s2temp[i]);
	}
	return (0);
}
