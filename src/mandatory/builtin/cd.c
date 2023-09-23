/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:43:31 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/23 02:22:39 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_path(t_list *envs, char *env_key);

void	cd(char **args, t_list *envs)
{
	size_t	argc;
	char	*path;

	argc = count_args(args);
	path = args[1];
	if (argc == 1)
	{
		path = get_env_path(envs, "HOME");
		if (path == NULL)
			return ;
	}
	else if (argc != 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return ;
	}
	else if (ft_strncmp(path, "-", 1) == 0)
	{
		path = get_env_path(envs, "OLDPWD");
		if (path == NULL)
			return ;
	}
	if (chdir(path) < 0)
		return (perror("minishell: cd"));
	uptade_pwd_env(envs);
}

static char	*get_env_path(t_list *envs, char *env_key)
{
	char	*path;

	path = find_env_value(envs, env_key);
	if (path == NULL)
	{
		ft_fprintf(2, "minishell: cd: %s not defined\n", env_key);
		return (NULL);
	}
	return (path);
}
