/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 00:34:30 by cobli             #+#    #+#             */
/*   Updated: 2023/09/22 00:57:46 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_list *envs, char *key)
{
	t_env	*env;

	while (envs != NULL)
	{
		env = envs->content;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
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
