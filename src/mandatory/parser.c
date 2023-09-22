/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:14:46 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 22:16:55 by luizedua         ###   ########.fr       */
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

bool	syntax_analysis(t_token_type *token_array)
{
	int	i;

	i = 0;
	if (token_array[0] < QUOTE || token_array[0] == CLOSE_PARENTHESIS)
		return (false);
	while (token_array[i] != END_ARRAY)
	{
		if (token_array[i] == PIPE && (token_array[i - 1] != WORD \
					|| token_array[i + 1] != WORD))
			return (false);
		else if (token_array[i] == REDIRECT_IN && (token_array[i - 1] != WORD \
					|| token_array[i + 1] != WORD))
			return (false);
		else if (token_array[i] == REDIRECT_OUT && (token_array[i - 1] != WORD \
					|| token_array[i + 1] != WORD))
			return (false);
		else if (token_array[i] == AND && (token_array[i - 1] != WORD \
					|| token_array[i + 1] != WORD))
			return (false);
		else if (token_array[i] == OR && (token_array[i - 1] != WORD \
					|| token_array[i + 1] != WORD))
			return (false);
		i++;
	}
	return (true);
}

void	print_token_array(int *token_array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%i,	", token_array[i]);
		ft_printf("\n");
		i++;
	}
}
