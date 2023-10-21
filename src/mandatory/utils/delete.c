/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:25:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/20 17:34:52 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(void *content)
{
	t_env	*env;

	env = content;
	free(env->key);
	free(env->value);
	free(env);
}

void	del_fd(void *content)
{
	t_fd	*fd;

	fd = content;
	if (fd->redirect_to != NULL)
	{
		free(fd->redirect_to);
		fd->redirect_to = NULL;
		free(content);
	}
}

void	del_token(void *content)
{
	t_token	*token;

	token = content;
	free(token->value);
	free(token);
}

void	free_token_array(t_list **token_array)
{
	size_t	i;

	i = -1;
	while (token_array[++i] != NULL)
		ft_lstclear(&token_array[i], del_token);
	free(token_array);
}
