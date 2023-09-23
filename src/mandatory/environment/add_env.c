/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:20:50 by cobli             #+#    #+#             */
/*   Updated: 2023/09/23 02:06:33 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_env(t_list *envs, char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (env);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	ft_lstadd_back(&envs, ft_lstnew(env));
	return (env);
}
