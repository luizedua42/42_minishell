/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:34:30 by cobli             #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_env	*find_env(t_list *envs, char *key)
{
	t_env	*env;

	while (envs != NULL)
	{
		env = envs->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
			return (env);
		envs = envs->next;
	}
	return (NULL);
}

char	*find_env_value(t_list *envs, char *key)
{
	t_env	*env;

	env = find_env(envs, key);
	if (env == NULL)
		return (NULL);
	return (env->value);
}

t_list	*find_env_element(t_list *envs, char *key)
{
	t_env	*env;

	while (envs != NULL)
	{
		env = envs->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}
