/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:20:50 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/23 23:46:45 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->envs = create_envs(envp);
	minishell->tokens = NULL;
	minishell->exit_status = EXIT_SUCCESS;
	minishell->fds.fd_in = STDIN_FILENO;
	minishell->fds.fd_out = STDOUT_FILENO;
	minishell->fds.fd_error = STDERR_FILENO;
}
