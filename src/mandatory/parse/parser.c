/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:14:46 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/25 20:49:54 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	simple_analysis(t_token_type *token_array);

bool	syntax_analysis(t_token_type *token_array)
{
	if (is_operator(token_array[0]) || token_array[0] == CLOSE_PARENTHESIS)
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
