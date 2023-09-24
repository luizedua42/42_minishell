/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:02:22 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 02:36:58 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_minishell *minishell, char **args)
{
	size_t	argc;
	t_list	*env;

	argc = count_args(args);
	if (argc == 1)
		return (EXIT_SUCCESS);
	args++;
	while (*args != NULL)
	{
		env = find_env_element(minishell->envs, *args);
		if (env == NULL)
		{
			args++;
			continue ;
		}
		ft_lstrm(minishell->envs, env, del_env);
		args++;
	}
	return (EXIT_SUCCESS);
}
