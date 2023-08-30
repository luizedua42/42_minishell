/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:14:55 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/18 13:05:35 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		nodecount;
	t_list	*temp;

	nodecount = 0;
	temp = lst;
	while (temp != NULL)
	{
		temp = temp->next;
		nodecount++;
	}
	return (nodecount);
}
