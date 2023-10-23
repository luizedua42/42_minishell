/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 23:57:41 by paulo             #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	errcheck(t_minishell *minishell, char *path, char **cmds, \
						char **env);

static int	handler_builtin(t_minishell *minishell, char **cmds);
static void	clear_all(t_minishell *minishell, char **cmds, char **env);
static int	print_err(char *format, char *path, int ret);

int	exec(char **cmds, t_minishell *minishell)
{
	int			ret;
	char		*path;
	char		**env;

	if (cmds == NULL)
	{
		clear_shell(minishell);
		return (EXIT_SUCCESS);
	}
	ret = handler_builtin(minishell, cmds);
	if (ret != -1)
		return (ret);
	env = ft_lst_to_array_choice(minishell->envs, select_env);
	if (ft_strchr(cmds[0], '/') == NULL)
		path = get_path(cmds[0], env);
	else
		path = cmds[0];
	ret = errcheck(minishell, path, cmds, env);
	if (ret != EXIT_SUCCESS)
		return (ret);
	execve(path, cmds, env);
	free(path);
	clear_all(minishell, cmds, env);
	perror(NULL);
	return (-1);
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

static int	errcheck(t_minishell *minishell, char *path, char **cmds, \
						char **env)
{
	struct stat	file_stat;
	int			ret;

	ret = EXIT_SUCCESS;
	if (path == NULL)
		ret = print_err("%s: command not found\n", cmds[0], COMMAND_NOT_FOUND);
	else if (stat(path, &file_stat) != -1 && S_ISDIR(file_stat.st_mode))
		ret = print_err("minishell: %s: Is a directory\n", path, PATH_ERROR);
	else if (access(path, F_OK) != 0)
		ret = print_err("minishell: %s: No such file or directory\n", path, \
						COMMAND_NOT_FOUND);
	else if (access(path, X_OK) != 0)
		ret = print_err("minishell: %s: Permission denied\n", path, PATH_ERROR);
	if (ret != EXIT_SUCCESS)
		clear_all(minishell, cmds, env);
	return (ret);
}

static int	print_err(char *format, char *path, int ret)
{
	ft_fprintf(STDERR_FILENO, format, path);
	return (ret);
}
