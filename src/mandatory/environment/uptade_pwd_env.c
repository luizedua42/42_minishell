/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uptade_pwd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:37:22 by cobli             #+#    #+#             */
/*   Updated: 2023/09/23 02:14:32 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	uptade_pwd_env(t_list *envs)
{
	char	*current_pwd;
	char	*old_pwd;

	current_pwd = getcwd(NULL, 0);
	old_pwd = find_env_value(envs, "PWD");
	update_env(envs, "OLDPWD", old_pwd);
	update_env(envs, "PWD", current_pwd);
	free(current_pwd);
}
