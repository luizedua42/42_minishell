/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:16:23 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/18 13:06:02 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*lastc;

	lastc = NULL;
	if (c == '\0')
	{
		return ((char *)&s[ft_strlen(s)]);
	}	
	while (*s != '\0' )
	{
		if ((char)c == *s)
			lastc = (char *)s;
		if (*(s + 1) == '\0')
			return (lastc);
		s++;
	}
	return (0);
}
