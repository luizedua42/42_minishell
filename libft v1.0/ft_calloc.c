/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:21:20 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/18 13:03:57 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	vartimes;

	vartimes = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (vartimes > __INT_MAX__ || vartimes / nmemb != size)
		return (NULL);
	mem = malloc(vartimes);
	if (mem != NULL)
		ft_bzero(mem, vartimes);
	return (mem);
}
