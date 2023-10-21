/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:57:41 by paulo             #+#    #+#             */
/*   Updated: 2023/10/21 00:41:57 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handler_builtin(t_minishell *minishell, char **cmds);
static void	clear_all(t_minishell *minishell, char **cmds, char **env);

int	exec(char **cmds, t_minishell *minishell)
{
	int			ret;
	char		*path;
	char		**env;
	struct stat	file_stat;

	ret = handler_builtin(minishell, cmds);
	if (ret != -1)
		return (ret);
	env = ft_lst_to_array_choice(minishell->envs, select_env);
	if (ft_strchr(cmds[0], '/') == NULL)
		path = get_path(cmds[0], env);
	else
		path = cmds[0];
	if (path == NULL)
	{
		ft_fprintf(2, "%s: command not found\n", cmds[0]);
		clear_all(minishell, cmds, env);
		return (COMMAND_NOT_FOUND);
	}
	if (stat(path, &file_stat) != -1 && S_ISDIR(file_stat.st_mode))
	{
		ft_fprintf(2, "minishell: %s: Is a directory\n", path);
		clear_all(minishell, cmds, env);
		return (126);
	}
	if (access(path, F_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: No such file or directory\n", path);
		clear_all(minishell, cmds, env);
		return (COMMAND_NOT_FOUND);
	}
	if (access(path, X_OK) != 0)
	{
		ft_fprintf(2, "minishell: %s: Permission denied\n", path);
		clear_all(minishell, cmds, env);
		return (126);
	}
	execve(path, cmds, env);
	free(path);
	clear_all(minishell, cmds, env);
	perror(NULL);
	return (errno);
}

static void	clear_all(t_minishell *minishell, char **cmds, char **env)
{
	clear_shell(minishell);
	free(cmds);
	ft_free_split(env);
}

static int	handler_builtin(t_minishell *minishell, char **cmds)
{
	int	ret;

	ret = builtin_selector(minishell, cmds, true);
	if (ret != -1)
	{
		free(cmds);
		clear_shell(minishell);
	}
	return (ret);
}
