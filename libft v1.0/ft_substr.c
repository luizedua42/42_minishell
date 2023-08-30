/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:19:25 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/18 15:31:46 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	if (start > s_len)
		return (ft_strdup(""));
	if (s_len - start >= len)
		new_s = malloc((len + 1) * sizeof(char));
	else
		new_s = malloc((s_len - start + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	if (new_s != NULL)
		ft_strlcpy(new_s, (s + start), (len + 1));
	return (new_s);
}
