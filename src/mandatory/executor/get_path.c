/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:06:27 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/25 16:35:55 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char **env);

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	*path_dir;
	char	**path;

	i = -1;
	path_dir = find_path(env);
	if (path_dir == NULL || path_dir[0] == '\0')
		return (cmd);
	path = ft_split(path_dir, ':');
	while (path[++i])
	{
		path_dir = ft_strjoin(path[i], "/");
		exec = ft_strjoin(path_dir, cmd);
		free(path_dir);
		if (access(exec, F_OK | X_OK) == 0)
			break ;
		free(exec);
		exec = NULL;
	}
	ft_free_split(path);
	return (exec);
}

static char	*find_path(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, PATH_STR, 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}
