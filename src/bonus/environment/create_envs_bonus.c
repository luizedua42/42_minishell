/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envs_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:00:26 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
	char	*first_equal;

	env = ft_calloc(1, sizeof(t_env));
	first_equal = ft_strchr(envp, '=');
	*first_equal = '\0';
	env->key = ft_strdup(envp);
	env->value = ft_strdup(first_equal + 1);
	return (env);
}
