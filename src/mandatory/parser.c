/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:14:46 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/20 21:25:29 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_analyzer(t_list *token_list)
{
	t_token *token_cont;
	
	token_cont = token_list->content;
	token_list = token_list->next;
	while (token_cont != NULL)
	{
		if (token_cont->type == PIPE)
			return (false);
	}
	return (true);
}