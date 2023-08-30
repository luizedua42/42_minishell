/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:51:04 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/11 13:21:40 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*nstring;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
		i++;
	nstring = malloc(i * sizeof(char) + 1);
	if (nstring == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		nstring[i] = f(i, s[i]);
		i++;
	}
	nstring[i] = '\0';
	return (nstring);
}
