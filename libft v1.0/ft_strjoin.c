/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:46:34 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/16 15:41:48 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		res_len;
	int		index;
	char	*n_string;

	index = 0;
	res_len = ft_strlen(s1) + ft_strlen(s2);
	n_string = malloc(res_len * sizeof(char) + 1);
	if (n_string == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		n_string[index] = *s1;
		index++;
		s1++;
	}
	while (*s2 != '\0')
	{
		n_string[index] = *s2;
		index++;
		s2++;
	}
	n_string[index] = '\0';
	return (n_string);
}
