/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:00:26 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/20 21:25:55 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env(char *envp);

t_list	*create_envs(char **envp)
{
	t_list	*envs;

	envs = NULL;
	while (*envp != NULL)
	{
		ft_lstadd_back(&envs, ft_lstnew(new_env(*envp)));
		envp++;
	}
	return (envs);
}

static t_env	*new_env(char *envp)
{
	t_env	*env;
	char	**strs;

	strs = ft_split(envp, '=');
	env = ft_calloc(1, sizeof(t_env));
	env->key = strs[0];
	env->value = strs[1];
	return (env);
}
