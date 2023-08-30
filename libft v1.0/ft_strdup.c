/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:07:45 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 13:02:04 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		c;

	if (s == NULL)
		return (NULL);
	c = 0;
	dup = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (dup == NULL)
		return (NULL);
	while (s[c])
	{
		dup[c] = s[c];
		c++;
	}
	dup[c] = '\0';
	return (dup);
}
