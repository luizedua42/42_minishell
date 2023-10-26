/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:14:47 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static size_t	pipe_quantize(t_list *tokens);

t_list	**split_pipes(t_list *tokens)
{
	size_t	i;
	t_token	*token;
	t_token	*tokendup;
	size_t	token_count;
	t_list	**token_array;

	i = 0;
	token_count = pipe_quantize(tokens);
	token_array = ft_calloc(token_count + 2, sizeof(t_list *));
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == PIPE)
			i++;
		else
		{
			tokendup = ft_calloc(1, sizeof(t_token));
			tokendup->type = token->type;
			if (token-> value != NULL)
				tokendup->value = ft_strdup(token->value);
			ft_lstadd_back(token_array + i, ft_lstnew(tokendup));
		}
		tokens = tokens->next;
	}
	return (token_array);
}

static size_t	pipe_quantize(t_list *tokens)
{
	t_token	*token;
	size_t	count;

	count = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

size_t	lst_matrix_len(t_list **matrix)
{
	size_t	size;

	size = 0;
	while (matrix[size] != NULL)
		size++;
	return (size);
}
