/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:42:17 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 23:22:48 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sanitize_tokens(t_minishell *minishell)
{
	t_list	*tokens;
	t_token	*token;

	tokens = minishell->tokens;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (!is_redirect(token->type))
		{
			tokens = tokens->next;
			continue ;
		}
		minishell->tokens = ft_lstrm(minishell->tokens, tokens->next,
				del_token);
		minishell->tokens = ft_lstrm(minishell->tokens, tokens, del_token);
		tokens = minishell->tokens;
	}
}
