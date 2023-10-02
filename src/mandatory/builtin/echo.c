/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 01:01:58 by cobli             #+#    #+#             */
/*   Updated: 2023/09/29 01:04:36 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	size_t	i;
	bool	n_is_set;

	i = 1;
	n_is_set = false;
	if (count_args(args) > 1)
	{
		while (args[i] && ft_strncmp("-n", args[i], 2) == 0)
		{
			n_is_set = true;
			i++;
		}
		while (args[i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1] && args[i][0] != '\0')
				ft_printf(" ");
			i++;
		}
	}
	if (n_is_set == 0)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
