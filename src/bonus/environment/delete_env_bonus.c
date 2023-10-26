/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:29:40 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

bool	delete_env(t_minishell *minishell, char *key)
{
	t_list	*env;

	env = find_env_element(minishell->envs, key);
	if (env == NULL)
		return (false);
	minishell->envs = ft_lstrm(minishell->envs, env, del_env);
	return (true);
}
