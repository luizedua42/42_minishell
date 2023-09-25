/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:12:46 by cobli             #+#    #+#             */
/*   Updated: 2023/09/24 23:31:19 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	token_analysis(t_token_type *token_array, t_token_type type)
{
	int	i;

	i = 1;
	while (token_array[i] != END_ARRAY)
	{
		if (token_array[i] == type && (!is_exe(token_array[i - 1])
				&& !is_exe(token_array[i + 1])))
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
	int i;
	int parenthesis_counter;

	i = 0;
	parenthesis_counter = 0;
	while (token_array[i] != END_ARRAY)
	{
		if (token_array[i] == OPEN_PARENTHESIS)
			parenthesis_counter++;
		if (token_array[i] == CLOSE_PARENTHESIS)
			parenthesis_counter--;
		if (parenthesis_counter < 0)
			return (false);
		i++;
	}
	if (parenthesis_counter != 0)
		return (false);
	return (true);
}