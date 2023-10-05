/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:12:46 by cobli             #+#    #+#             */
/*   Updated: 2023/10/04 21:13:52 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_parenthesis_syntax(t_token_type *token_array, int i, \
	int *parenthesis_counter);

bool	token_analysis(t_token_type *token_array, t_token_type type)
{
	int	i;

	i = 1;
	while (token_array[i] != END_ARRAY)
	{
		if (token_array[i] == type && ((!is_exe(token_array[i - 1]) \
			&& token_array[i - 1] != CLOSE_PARENTHESIS) \
				|| (!is_exe(token_array[i + 1]) && token_array[i + 1] \
					!= OPEN_PARENTHESIS)))
			return (false);
		i++;
	}
	return (true);
}

bool	redirection_analysis(t_token_type *token_array)
{
	int	i;

	i = 0;
	while (token_array[i] != END_ARRAY)
	{
		if (is_redirect(token_array[i]) && !is_exe(token_array[i + 1]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_parenthesis(t_token_type *token_array)
{
	int	i;
	int	parenthesis_counter;

	i = 0;
	parenthesis_counter = 0;
	while (token_array[i] != END_ARRAY)
	{
		if (!check_parenthesis_syntax(token_array, i, &parenthesis_counter))
			return (false);
		if (parenthesis_counter < 0)
			return (false);
		i++;
	}
	if (parenthesis_counter != 0)
		return (false);
	return (true);
}

static bool	check_parenthesis_syntax(t_token_type *token_array, int i, \
	int *parenthesis_counter)
{
	if (token_array[i] == OPEN_PARENTHESIS)
	{
		if (i > 0 && !is_operator(token_array[i - 1]) && token_array[i - 1]
			!= OPEN_PARENTHESIS)
			return (false);
		if (is_operator(token_array[i + 1]))
			return (false);
		(*parenthesis_counter)++;
	}
	if (token_array[i] == CLOSE_PARENTHESIS)
	{
		if (is_operator(token_array[i - 1]))
			return (false);
		if ((!is_operator(token_array[i + 1]) && \
			!is_redirect(token_array[i + 1])) && token_array[i + 1] \
			!= END_ARRAY && token_array[i + 1] != CLOSE_PARENTHESIS)
			return (false);
		(*parenthesis_counter)--;
	}
	return (true);
}
