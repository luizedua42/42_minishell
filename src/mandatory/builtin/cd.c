/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:43:31 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/24 15:43:46 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_path(t_list *envs, char *env_key, char **path);

int	cd(t_minishell *minishell, char **args)
{
	size_t	argc;
	char	*path;
	int		exit_status;

	argc = count_args(args);
	path = args[1];
	exit_status = EXIT_SUCCESS;
	if (argc == 1)
		exit_status = get_env_path(minishell->envs, "HOME", &path);
	else if (argc != 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return (EXIT_FAILURE);
	}
	else if (ft_strncmp(path, "-", 1) == 0)
		exit_status = get_env_path(minishell->envs, "OLDPWD", &path);
	if (chdir(path) < 0)
	{
		perror("minishell: cd");
		exit_status = EXIT_FAILURE;
	}
	uptade_pwd_env(minishell->envs);
	return (exit_status);
}

static int	get_env_path(t_list *envs, char *env_key, char **path)
{
	*path = find_env_value(envs, env_key);
	if (*path == NULL)
	{
		ft_fprintf(2, "minishell: cd: %s not defined\n", env_key);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
