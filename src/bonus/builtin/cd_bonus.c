/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:43:31 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/25 16:48:40 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	get_env_path(t_list *envs, char *env_key, char **path);
static void	print_error(char *path);

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
	else if (ft_strncmp(path, "-", 2) == 0)
		exit_status = get_env_path(minishell->envs, "OLDPWD", &path);
	if (exit_status != EXIT_FAILURE && chdir(path) < 0)
	{
		print_error(path);
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
		ft_fprintf(2, "minishell: cd: %s not set\n", env_key);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	print_error(char *path)
{
	char	*error_message;

	error_message = ft_strjoin("minishell: cd: ", path);
	perror(error_message);
	free(error_message);
}
