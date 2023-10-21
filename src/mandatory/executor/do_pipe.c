/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:05:33 by paulo             #+#    #+#             */
/*   Updated: 2023/10/21 01:41:18 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child(int *pipedes, int i, t_minishell *minishell,
				t_list **token_array);
static void	handle_father(bool is_last, int *pipedes, int i, int *hostage_pipe);
static int	handle_builtin(t_minishell *minishell, t_list *tokens,
				t_list **token_array);
static void	exit_child(t_list **token_array, bool close_first, bool close_last,
				int ret);

int	do_pipe(t_minishell *minishell, t_list *tokens, size_t i,
		t_list **token_array)
{
	pid_t		pid;
	int			pipedes[3];
	static int	hostage_pipe;
	bool		is_last;

	pipedes[0] = -1;
	pipedes[1] = -1;
	pipedes[2] = -1;
	is_last = token_array[i + 1] == NULL;
	sanitize_emptyvar(token_array);
	if (token_array[i] == NULL)
	{
		minishell->exit_status = EXIT_SUCCESS;
		return (EXIT_FAILURE);
	}
	if (i == 0 && is_last && is_builtin(((t_token *)tokens->content)->value))
		return (handle_builtin(minishell, tokens, token_array));
	if (pipe_validation(is_last, pipedes, hostage_pipe))
		return (-1);
	handle_signal_child();
	pid = fork();
	if (fork_validation(pid) == -1)
		return (-1);
	if (!pid)
		handle_child(pipedes, i, minishell, token_array);
	else
		handle_father(is_last, pipedes, i, &hostage_pipe);
	return (pid);
}

static void	handle_father(bool is_last, int *pipedes, int i, int *hostage_pipe)
{
	if (!is_last)
	{
		if (i != 0)
			close(*hostage_pipe);
		*hostage_pipe = dup(pipedes[0]);
		close(pipedes[0]);
		close(pipedes[1]);
	}
	else if (*hostage_pipe != 0)
		close(*hostage_pipe);
}

static void	handle_child(int *pipedes, int i, t_minishell *minishell,
		t_list **token_array)
{
	char	**cmds;
	int		ret;
	bool	is_last;
	t_list	*child_files;
	int		last_fd;

	is_last = token_array[i + 1] == NULL;
	if (!is_last)
		close(pipedes[0]);
	child_files = get_redirects(token_array[i]);
	open_redirects(minishell, child_files, token_array, true);
	last_fd = get_last_fd(STDIN_FILENO, child_files, pipedes[2]);
	if (i != 0 || last_fd != pipedes[2])
		my_dup(last_fd, STDIN_FILENO);
	last_fd = get_last_fd(STDOUT_FILENO, child_files, pipedes[1]);
	if (!is_last || last_fd != pipedes[1])
		my_dup(last_fd, STDOUT_FILENO);
	sanitize_tokens(&token_array[i]);
	cmds = ft_lst_to_array_choice(token_array[i], select_token_value);
	ret = exec(cmds, minishell);
	close_fds(child_files);
	ft_lstclear(&child_files, del_fd);
	exit_child(token_array, i != 0 || last_fd != pipedes[2], !is_last
		|| last_fd != pipedes[1], ret);
}

static void	exit_child(t_list **token_array, bool close_first, bool close_last,
		int ret)
{
	free_token_array(token_array);
	if (close_first)
		close(STDIN_FILENO);
	if (close_last)
		close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(ret);
}

static int	handle_builtin(t_minishell *minishell, t_list *tokens,
		t_list **token_array)
{
	char	**cmds;
	int		ret;
	size_t	i;
	t_list	*child_files;
	int		last_fdin;
	int		last_fdout;
	int		safe_in;
	int		safe_out;

	child_files = get_redirects(tokens);
	if (!open_redirects(minishell, child_files, token_array, false))
		return (EXIT_FAILURE);
	sanitize_tokens(&tokens);
	cmds = ft_lst_to_array_choice(tokens, select_token_value);
	last_fdin = get_last_fd(STDIN_FILENO, child_files, -1);
	if (last_fdin != -1)
	{
		safe_in = dup(STDIN_FILENO);
		my_dup(last_fdin, STDIN_FILENO);
	}
	last_fdout = get_last_fd(STDOUT_FILENO, child_files, -1);
	if (last_fdout != -1)
	{
		safe_out = dup(STDOUT_FILENO);
		my_dup(last_fdout, STDOUT_FILENO);
	}
	ft_lstclear(&child_files, del_fd);
	ret = builtin_selector(minishell, cmds, false);
	if (ft_strncmp(cmds[0], "exit", 5) == 0)
	{
		if (ret != -2)
		{
			free(cmds);
			i = -1;
			while (token_array[++i] != NULL)
				ft_lstclear(&token_array[i], del_token);
			free(token_array);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			exit(ret);
		}
		else
		{
			free(cmds);
			minishell->exit_status = EXIT_FAILURE;
			return (EXIT_FAILURE);
		}
	}
	if (last_fdin != -1)
		my_dup(safe_in, STDIN_FILENO);
	if (last_fdout != -1)
		my_dup(safe_out, STDOUT_FILENO);
	free(cmds);
	minishell->exit_status = ret;
	return (ret);
}
