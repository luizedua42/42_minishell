/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:27:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/11 20:56:49 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_pipe(t_minishell minishell, t_list *tokens, bool is_last);

int	executor(t_minishell minishell)
{
	size_t	i;
	int		fd_in;
	int		fd_out;
	t_list	**token_array;

	i = 0;
	if (minishell.fds.fd_in.type == HEREDOC_IN)
		here_doc(&minishell, &minishell.fds.fd_in);
	else if (minishell.fds.fd_in.type == REDIRECT_IN)
	{
		fd_in = open_file(&minishell, &minishell.fds.fd_in);
		dup2(fd_in, STDIN_FILENO);
	}
	expand_all(&minishell, minishell.tokens);
	token_array = split_pipes(minishell.tokens);
	while (token_array[i] != NULL)
	{
		do_pipe(minishell, token_array[i], token_array[i + 1] == NULL);
		i++;
	}
	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
	if (minishell.fds.fd_out.type != END_ARRAY)
	{
		fd_out = open_file(&minishell, &minishell.fds.fd_out);
		dup2(fd_out, STDOUT_FILENO);	
	}
	return (errno);
}

void	exec(char **cmds, t_minishell *minishell)
{
	int		ret;
	char	*path;
	char	**env;

	ret = builtin_selector(minishell, cmds);
	if (ret != -1)
	{
		free(cmds);
		exit(ret);
	}
	env = ft_lst_to_array_choice(minishell->envs, select_env);
	if (ft_strchr(cmds[0], '/') == NULL)
		path = get_path(cmds[0], env);
	else
		path = cmds[0];
	if (path == NULL && access(path, F_OK | X_OK) != 0)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmds[0], STDERR_FILENO);
		free(cmds);
		ft_free_split(env);
		exit(COMMAND_NOT_FOUND);
	}
	execve(path, cmds, env);
	free(path);
	free(cmds);
	ft_free_split(env);
	perror(NULL);
	exit(errno);
}

static void	do_pipe(t_minishell minishell, t_list *tokens, bool is_last)
{
	pid_t	pid;
	t_token *token;
	char	**cmds;
	int		pipedes[2];

	token = tokens->content;
	if (!is_last && pipe(pipedes) == -1)
	{
		perror(NULL);
		exit(errno);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		exit(errno);
	}
	if (!pid)
	{
		if (!is_last)
		{
			close(pipedes[0]);
			dup2(pipedes[1], STDOUT_FILENO);
		}
		if (token->type == SHELL)
		{
			executor(*(t_minishell *)minishell.shells->content);
			minishell.shells->content = minishell.shells->next;
		}
		else
		{
			cmds = ft_lst_to_array_choice(tokens, select_token_value);
			exec(cmds, &minishell);
		}
	}
	else
	{
		if (!is_last)
		{
			close(pipedes[1]);
			dup2(pipedes[0], STDIN_FILENO);
		}
		wait(NULL);
	}
}
