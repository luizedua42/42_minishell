/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:42:17 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/21 20:13:52 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sanitize_tokens(t_list **original_tokens)
{
	t_list	*tokens;
	t_token	*token;

	tokens = *original_tokens;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (!is_redirect(token->type))
		{
			tokens = tokens->next;
			continue ;
		}
		*original_tokens = ft_lstrm(*original_tokens, tokens->next, del_token);
		*original_tokens = ft_lstrm(*original_tokens, tokens, del_token);
		tokens = *original_tokens;
	}
}

void	sanitize_emptyvar(t_list **original_tokens)
{
	t_list	*tokens;
	t_token	*token;

	tokens = *original_tokens;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->value == NULL)
		{
			*original_tokens = ft_lstrm(*original_tokens, tokens, del_token);
			tokens = *original_tokens;
			continue ;
		}
		tokens = tokens->next;
	}
}
