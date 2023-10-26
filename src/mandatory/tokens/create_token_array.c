/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:56:22 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/25 16:17:52 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	*create_token_array(t_list *tokens)
{
	size_t			size;
	t_token_type	*token_array;
	t_token			*token;
	size_t			i;

	if (tokens == NULL)
		return (NULL);
	size = ft_lstsize(tokens);
	token_array = ft_calloc((size + 1), sizeof(t_token_type));
	if (token_array == NULL)
		return (NULL);
	i = 0;
	while (i < size && tokens != NULL)
	{
		token = tokens->content;
		token_array[i] = token->type;
		tokens = tokens->next;
		i++;
	}
	token_array[i] = END_ARRAY;
	return (token_array);
}
