/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:16:57 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/17 12:44:25 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_counter(long int nb)
{
	int	c;

	c = 0;
	if (nb == 1)
		return (1);
	while (nb)
	{
		nb = nb / 10;
		c++;
	}
	return (c);
}

static void	break_numbers(long int nb, char *pointer_to_number, long int *i)
{
	if (nb > 9)
		break_numbers((nb / 10), pointer_to_number, i);
	nb = nb % 10;
	pointer_to_number[(*i)++] = nb + 48;
}

char	*ft_itoa(int n)
{
	long int	i;
	long int	nb;
	long int	digits_size;
	char		*allocated_number;

	i = 0;
	nb = (long int)n;
	digits_size = digits_counter(nb);
	if (nb <= 0)
		digits_size++;
	allocated_number = malloc((digits_size + 1) * sizeof(char));
	if (allocated_number == (void *)0)
		return (NULL);
	if (nb < 0)
	{
		allocated_number[i++] = '-';
		nb = nb * -1;
	}
	break_numbers(nb, allocated_number, &i);
	allocated_number[digits_size] = '\0';
	return (allocated_number);
}
