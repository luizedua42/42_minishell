/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 01:01:58 by cobli             #+#    #+#             */
/*   Updated: 2023/10/25 15:36:54 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n(char *str);

int	echo(char **args)
{
	size_t	i;
	bool	n_is_set;

	i = 1;
	n_is_set = false;
	if (count_args(args) > 1)
	{
		while (args[i] && is_n(args[i]))
		{
			n_is_set = true;
			i++;
		}
		while (args[i])
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			if (args[i + 1] && args[i][0] != '\0')
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	if (n_is_set == false)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

static bool	is_n(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	while (str[i] == 'n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (true);
	return (false);
}
