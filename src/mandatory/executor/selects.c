/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:50:25 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/11 19:50:43 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*select_token_value(void *token)
{
	return (((t_token *)token)->value);
}

void *select_env(void *content)
{
	t_env	*env;
	char	*env_key;
	char	*env_value;

	env = content;
	env_key = ft_strjoin(env->key, "=");
	env_value = ft_strjoin(env_key, env->value);
	free(env_key);
	return (env_value);
}