/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:27:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	mini_return(t_minishell *minishell, int status);

int	executor(t_minishell *minishell)
{
	size_t	i;
	t_list	**token_array;
	size_t	lst_size;
	int		status;

	status = EXIT_SUCCESS;
	if (expand_all(minishell, minishell->tokens) == false)
		return (CTRLC_RETURN);
	token_array = split_pipes(minishell->tokens);
	lst_size = lst_matrix_len(token_array);
	minishell->pids = ft_calloc(lst_size, sizeof(int));
	i = -1;
	while (token_array[++i] != NULL)
		minishell->pids[i] = do_pipe(minishell, token_array[i], i, token_array);
	i = 0;
	while (i < lst_size)
		waitpid(minishell->pids[i++], &status, 0);
	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
	return (mini_return(minishell, status));
}

static int	mini_return(t_minishell *minishell, int status)
{
	if (minishell->exit_status != 0)
		return (minishell->exit_status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}
