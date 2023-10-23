/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlinks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:23:52 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 19:51:24 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all(t_list *tokens)
{
	t_token	*token;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == HEREDOC_IN)
		{
			tokens = tokens->next;
			token = tokens->content;
			unlink(token->value);
		}
		tokens = tokens->next;
	}
}
