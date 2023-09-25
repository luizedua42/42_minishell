/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:33:57 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/24 15:44:36 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_minishell *minishell)
{
	t_list	*envs;
	t_env	*env;

	envs = minishell->envs;
	while (envs != NULL)
	{
		env = envs->content;
		ft_printf("%s=%s\n", env->key, env->value);
		envs = envs->next;
	}
	return (EXIT_SUCCESS);
}
