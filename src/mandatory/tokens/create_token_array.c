/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:56:22 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 11:56:32 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	*create_token_array(t_list *tokens, int *i)
{
	int				size;
	t_token_type	*token_array;
	t_token			*token_cont;

	size = ft_lstsize(tokens);
	token_array = ft_calloc((size + 1), sizeof(int));
	while (*i < size && tokens != NULL)
	{
		token_cont = tokens->content;
		token_array[*i] = token_cont->type;
		tokens = tokens->next;
		(*i)++;
	}
	token_array[*i] = END_ARRAY;
	return (token_array);
}
