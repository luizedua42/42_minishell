/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:20:50 by cobli             #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_env	*update_env(t_list *envs, char *key, char *value)
{
	t_env	*env;

	env = find_env(envs, key);
	if (env == NULL)
		return (NULL);
	if (env->value != NULL)
		free(env->value);
	env->value = ft_strdup(value);
	return (env);
}

t_env	*export_env(t_minishell *minishell, char *key, char *value)
{
	t_env	*env;

	env = update_env(minishell->envs, key, value);
	if (env == NULL)
		return (add_env(minishell->envs, key, value));
	return (env);
}
