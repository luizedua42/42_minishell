/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:33:57 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 22:18:06 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *envs)
{
	t_env	*env;

	while (envs != NULL)
	{
		env = envs->content;
		ft_printf("%s=%s\n", env->key, env->value);
		envs = envs->next;
	}
}
