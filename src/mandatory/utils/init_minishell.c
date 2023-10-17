/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:20:50 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/16 23:35:17 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pwd_env(t_minishell *minishell);

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	minishell->envs = create_envs(envp);
	create_pwd_env(minishell);
	minishell->exit_status = EXIT_SUCCESS;
	minishell->fds.fd_in.type = END_ARRAY;
	minishell->fds.fd_out.type = END_ARRAY;
	minishell->fds.fd_error.type = END_ARRAY;
	return (minishell);
}

static void	create_pwd_env(t_minishell *minishell)
{
	char	*current_pwd;
	t_env	*pwd_env;

	current_pwd = getcwd(NULL, 0);
	pwd_env = find_env(minishell->envs, "PWD");
	if (pwd_env == NULL)
		add_env(minishell->envs, "PWD", current_pwd);
	else
		update_env(minishell->envs, "PWD", current_pwd);
	pwd_env = find_env(minishell->envs, "OLDPWD");
	if (pwd_env == NULL)
		add_env(minishell->envs, "OLDPWD", current_pwd);
	else
		update_env(minishell->envs, "OLDPWD", current_pwd);
	free(current_pwd);
}
