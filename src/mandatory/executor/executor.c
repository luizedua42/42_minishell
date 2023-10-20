/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 03:27:00 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/20 00:37:41 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_minishell *minishell)
{
	size_t	i;
	t_list	**token_array;
	size_t	lst_size;

	expand_all(minishell, minishell->tokens);
	token_array = split_pipes(minishell->tokens);
	lst_size = lst_matrix_len(token_array);
	minishell->pids = ft_calloc(lst_size, sizeof(int));
	i = -1;
	while (token_array[++i] != NULL)
		minishell->pids[i] = do_pipe(minishell, token_array[i], i, token_array);
	i = 0;
	while (i < lst_size)
		waitpid(minishell->pids[i++], NULL, 0);
	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
	return (errno);
}
