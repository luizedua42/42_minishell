/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:02:22 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	unset(t_minishell *minishell, char **args)
{
	size_t	argc;

	argc = count_args(args);
	if (argc == 1)
		return (EXIT_SUCCESS);
	args++;
	while (*args != NULL)
	{
		if (delete_env(minishell, *args))
			break ;
		args++;
	}
	return (EXIT_SUCCESS);
}
