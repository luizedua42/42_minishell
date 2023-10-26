/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:02:22 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static bool	check_parameter(char *str);

int	unset(t_minishell *minishell, char **args)
{
	size_t	i;
	size_t	argc;
	size_t	valid_args;
	bool	is_valid_args;

	i = 0;
	argc = count_args(args);
	valid_args = 0;
	if (argc == 1)
		return (EXIT_SUCCESS);
	while (args[++i] != NULL)
	{
		is_valid_args = check_parameter(args[i]);
		valid_args += is_valid_args;
		if (!is_valid_args)
			continue ;
		delete_env(minishell, args[i]);
	}
	if (valid_args < argc - 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	check_parameter(char *str)
{
	size_t	i;
	bool	is_valid;

	i = 0;
	is_valid = true;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (ft_isdigit(str[0]) || str[0] == '=' || !is_valid || str[0] == '\0')
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier\n", str);
		return (false);
	}
	return (true);
}
