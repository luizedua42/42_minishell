/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 23:20:50 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	create_pwd_env(t_minishell *minishell);

t_minishell	*init_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = ft_calloc(1, sizeof(t_minishell));
	getset_mini(minishell);
	minishell->envs = create_envs(envp);
	create_pwd_env(minishell);
	minishell->exit_status = EXIT_SUCCESS;
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
	pwd_env = find_env(minishell->envs, "OLDPWD");
	if (pwd_env == NULL)
		add_env(minishell->envs, "OLDPWD", current_pwd);
	free(current_pwd);
}
