 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:27:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/16 20:04:00 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_pipe(t_minishell *minishell, t_list *tokens, bool is_last, size_t i, int *pids, t_list **token_array, t_minishell *original_minishell);
static int	exec(char **cmds, t_minishell *minishell, int *pids, t_list **token_array, t_minishell *original_minishell);

int	executor(t_minishell *minishell, t_minishell *original_minishell)
{
	size_t	i;
	t_list	**token_array;
	size_t	lst_size;
	int		*pid;

	i = 0;
	expand_all(minishell, minishell->tokens);
	token_array = split_pipes(minishell->tokens);
	lst_size = lst_matrix_len(token_array);
	pid = ft_calloc(lst_size, sizeof(int));
	while (token_array[i] != NULL)
	{
		pid[i] = do_pipe(minishell, token_array[i], token_array[i + 1] == NULL, i, pid, token_array, original_minishell);
		i++;
	}
	i = 0;
	while (i < lst_size)
		waitpid(pid[i++], NULL, 0);
	free(pid);
	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
	return (errno);
}

static int	exec(char **cmds, t_minishell *minishell, int *pids, t_list **token_array, t_minishell *original_minishell)
{
	int		ret;
	char	*path;
	char	**env;
	size_t	i;

	i = -1;
	ret = builtin_selector(minishell, cmds);
	if (ret != -1)
	{
		free(cmds);
		free(pids);
		ft_lstclear(&original_minishell->tokens, del_token);
		ft_lstclear(&original_minishell->envs, del_env);
		clear_fds(original_minishell);
		ft_lstclear(&minishell->tokens, del_token);
		ft_lstclear(&minishell->envs, del_env);
		clear_fds(minishell);
		clear_shells(minishell);
		while (token_array[++i] != NULL)
			ft_lstclear(&token_array[i], del_token);
		free(token_array);
		return (ret);
	}
	env = ft_lst_to_array_choice(minishell->envs, select_env);
	if (ft_strchr(cmds[0], '/') == NULL)
		path = get_path(cmds[0], env);
	else
		path = cmds[0];
	if (path == NULL || access(path, F_OK | X_OK) != 0)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmds[0], STDERR_FILENO);
		free(cmds);
		ft_free_split(env);
		free(pids);
		ft_lstclear(&original_minishell->tokens, del_token);
		ft_lstclear(&original_minishell->envs, del_env);
		clear_fds(original_minishell);
		ft_lstclear(&minishell->tokens, del_token);
		ft_lstclear(&minishell->envs, del_env);
		clear_fds(minishell);
		clear_shells(minishell);
		while (token_array[++i] != NULL)
			ft_lstclear(&token_array[i], del_token);
		free(token_array);
		return (COMMAND_NOT_FOUND);
	}
	execve(path, cmds, env);
	free(pids);
	ft_lstclear(&original_minishell->tokens, del_token);
	ft_lstclear(&original_minishell->envs, del_env);
	clear_fds(original_minishell);
	ft_lstclear(&minishell->tokens, del_token);
	ft_lstclear(&minishell->envs, del_env);
	clear_fds(minishell);
	clear_shells(minishell);
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
	free(path);
	free(cmds);
	ft_free_split(env);
	perror(NULL);
	return (errno);
}

static int	do_pipe(t_minishell *minishell, t_list *tokens, bool is_last, size_t i, int *pids, t_list **token_array, t_minishell *original_minishell)
{
	pid_t		pid;
	char		**cmds;
	int			pipedes[2];
	static int	hostage_pipe;
	int			ret;

	if (i == 0 && is_last && is_builtin(((t_token *) tokens->content)->value))
	{
		cmds = ft_lst_to_array_choice(tokens, select_token_value);
		ret = builtin_selector(original_minishell, cmds);
		free(cmds);
		return (ret);
	}
	if (!is_last && pipe(pipedes) == -1)
	{
		perror(NULL);
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		return (-1);
	}
	if (!pid)
	{
		if (!is_last)
			close(pipedes[0]);
		if (i != 0)
		{
			dup2(hostage_pipe, STDIN_FILENO);
			close(hostage_pipe);
		}
		if (!is_last)
		{
			dup2(pipedes[1], STDOUT_FILENO);
			close(pipedes[1]);
		}
		cmds = ft_lst_to_array_choice(tokens, select_token_value);
		ret = exec(cmds, minishell, pids, token_array, original_minishell);
		if (!is_last)
			close(STDOUT_FILENO);
		if (i != 0)
			close(STDIN_FILENO);
		exit(ret);
	}
	else if (!is_last)
	{
		if (i != 0)
			close(hostage_pipe);
		hostage_pipe = dup(pipedes[0]);
		close(pipedes[0]);
		close(pipedes[1]);
	}
	else if (hostage_pipe != 0)
		close(hostage_pipe);
	return (pid);
}
