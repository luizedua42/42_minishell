/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:05:33 by paulo             #+#    #+#             */
/*   Updated: 2023/10/18 22:11:15 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child(int *pipedes, int i,
				t_minishell *minishell, t_list **token_array);
static void	handle_father(bool is_last, int *pipedes, int i, int *hostage_pipe);
static int	handle_builtin(t_minishell *minishell, t_list *tokens,
				t_list **token_array);
static void	free_token_array(t_list **token_array);

int	do_pipe(t_minishell *minishell, t_list *tokens, size_t i,
		t_list **token_array)
{
	pid_t		pid;
	int			pipedes[2];
	static int	hostage_pipe;
	bool		is_last;

	is_last = token_array[i + 1] == NULL;
	if (i == 0 && is_last && is_builtin(((t_token *)tokens->content)->value))
		return (handle_builtin(minishell, tokens, token_array));
	if (pipe_validation(is_last, pipedes))
		return (-1);
	handle_signal_child();
	pid = fork();
	if (fork_validation(pid) == -1)
		return (-1);
	if (!pid)
	{
		if (i != 0)
			my_dup(hostage_pipe, STDIN_FILENO);
		handle_child(pipedes, i, minishell, token_array);
	}
	else
		handle_father(is_last, pipedes, i, &hostage_pipe);
	return (pid);
}

static void	free_token_array(t_list **token_array)
{
	size_t	i;

	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
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

static void	handle_child(int *pipedes, int i,
		t_minishell *minishell, t_list **token_array)
{
	char	**cmds;
	int		ret;
	bool	is_last;
	t_list	*child_files;
	int		last_fd;

	child_files = get_redirects(token_array[i]);
	if(analyse_fds(child_files, minishell->fds) == false)
		exit(EXIT_FAILURE);
	is_last = token_array[i + 1] == NULL;
	last_fd = get_last_fd(STDIN_FILENO, child_files);
	if (last_fd != -2)
		my_dup(last_fd, STDIN_FILENO);
	else
		;
	last_fd = get_last_fd(STDOUT_FILENO, child_files);
	if (last_fd != -2)
		my_dup(last_fd, STDOUT_FILENO);
	else if (!is_last)
		my_dup(pipedes[1], STDOUT_FILENO);
	if (!is_last)
		close(pipedes[0]);
	sanitize_tokens(minishell);
	cmds = ft_lst_to_array_choice(token_array[i], select_token_value);
	ret = exec(cmds, minishell);
	free_token_array(token_array);
	if (!is_last)
		close(STDOUT_FILENO);
	if (i != 0)
		close(STDIN_FILENO);
	exit(ret);
}

static int	handle_builtin(t_minishell *minishell, t_list *tokens,
			t_list **token_array)
{
	char	**cmds;
	int		ret;
	size_t	i;

	cmds = ft_lst_to_array_choice(tokens, select_token_value);
	ret = builtin_selector(minishell, cmds, false);
	if (ft_strncmp(cmds[0], "exit", 4) == 0)
	{
		if (ret != -2)
		{
			free(cmds);
			i = -1;
			while (token_array[++i] != NULL)
				ft_lstclear(&token_array[i], del_token);
			free(token_array);
			exit(ret);
		}
		else
		{
			free(cmds);
			return (EXIT_FAILURE);
		}
	}
	free(cmds);
	return (ret);
}
