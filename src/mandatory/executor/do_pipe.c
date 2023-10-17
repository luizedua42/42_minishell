/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:05:33 by paulo             #+#    #+#             */
/*   Updated: 2023/10/17 00:53:51 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child(bool is_last, int *pipedes, int i,
				t_minishell *minishell, t_list **token_array);
static void	handle_father(bool is_last, int *pipedes, int i, int *hostage_pipe);
static int	handle_builtin(t_minishell *minishell, t_list *tokens);
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
		return (handle_builtin(minishell, tokens));
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
		if (i != 0)
			my_dup(hostage_pipe, STDIN_FILENO);
		handle_child(is_last, pipedes, i, minishell, token_array);
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

static void	handle_child(bool is_last, int *pipedes, int i,
		t_minishell *minishell, t_list **token_array)
{
	char	**cmds;
	int		ret;

	if (!is_last)
		close(pipedes[0]);
	if (!is_last)
		my_dup(pipedes[1], STDOUT_FILENO);
	cmds = ft_lst_to_array_choice(token_array[i], select_token_value);
	ret = exec(cmds, minishell);
	free_token_array(token_array);
	if (!is_last)
		close(STDOUT_FILENO);
	if (i != 0)
		close(STDIN_FILENO);
	exit(ret);
}

static int	handle_builtin(t_minishell *minishell, t_list *tokens)
{
	char	**cmds;
	int		ret;

	cmds = ft_lst_to_array_choice(tokens, select_token_value);
	ret = builtin_selector(minishell, cmds);
	free(cmds);
	return (ret);
}
