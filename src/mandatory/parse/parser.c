/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:14:46 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/24 23:29:57 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	simple_analysis(t_token_type *token_array);

bool	syntax_analysis(t_token_type *token_array)
{
	if (token_array[0] < REDIRECT_IN || token_array[0] == CLOSE_PARENTHESIS)
		return (false);
	if (simple_analysis(token_array) == false)
		return (false);
	return (true);
}

static bool	simple_analysis(t_token_type *token_array)
{
	if (token_analysis(token_array, PIPE) == false)
		return (false);
	else if (token_analysis(token_array, AND) == false)
		return (false);
	else if (token_analysis(token_array, OR) == false)
		return (false);
	else if (redirection_analysis(token_array) == false)
		return (false);
	else if (check_parenthesis(token_array) == false)
		return (false);
	return (true);
}
