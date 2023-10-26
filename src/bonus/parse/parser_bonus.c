/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:14:46 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static size_t	count_tokens(t_token_type *token_array);

bool	syntax_analysis(t_token_type *token_array)
{
	size_t	tokens_len;

	if (token_array == NULL)
		return (false);
	tokens_len = count_tokens(token_array);
	if (token_array[0] == PIPE || token_array[tokens_len - 1] == PIPE)
		return (false);
	if (redirection_analysis(token_array) == false)
		return (false);
	return (true);
}

static size_t	count_tokens(t_token_type *token_array)
{
	size_t	size;

	size = 0;
	while (token_array[size] != END_ARRAY)
		size++;
	return (size);
}
