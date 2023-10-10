/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:27:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/09 22:09:52 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_pipe(t_minishell *minishell, t_list *tokens);

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
		do_pipe(&minishell, minishell.tokens);
	if (minishell.fds.fd_out.type != END_ARRAY)
	{
		fd_out = open_file(&minishell, &minishell.fds.fd_out);
		dup2(fd_out, STDOUT_FILENO);	
	}
	exec(argv[current_cmd], env);
}

void	exec(char **cmds, char **env)
{
	char	*path;

	if (ft_strchr(cmds[0], '/') == NULL)
		path = get_path(cmds[0], env);
	else
		path = cmds[0];
	if (path == NULL)
	{
		ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmds[0], STDERR_FILENO);
		ft_free_split(cmds);
		exit(COMMAND_NOT_FOUND);
	}
	execve(path, cmds, env);
	free(path);
	ft_free_split(cmds);
	perror(NULL);
	exit(errno);
}

static void	do_pipe(t_minishell minishell, t_list *tokens)
{
	pid_t	pid;
	t_token *token;
	int		pipedes[2];

	token = tokens->content;
	if (pipe(pipedes) == -1)
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
		close(pipedes[0]);
		dup2(pipedes[1], STDOUT_FILENO);
		if (token->type == SHELL)
		{
			executor(*(t_minishell *)minishell.shells->content);
			minishell.shells->content = minishell.shells->next;
		}
		else
			ft_lst_to_array(tokens);
		exec(cmd, env);
	}
	else
	{
		close(pipedes[1]);
		dup2(pipedes[0], STDIN_FILENO);
	}
}
