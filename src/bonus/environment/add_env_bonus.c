/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:20:50 by cobli             #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_env	*add_env(t_list *envs, char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (env == NULL)
		return (env);
	env->key = ft_strdup(key);
	if (value == NULL)
		env->value = NULL;
	else
		env->value = ft_strdup(value);
	ft_lstadd_back(&envs, ft_lstnew(env));
	return (env);
}
