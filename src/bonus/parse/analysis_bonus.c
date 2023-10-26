/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analysis_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:12:46 by cobli             #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

bool	redirection_analysis(t_token_type *token_array)
{
	int	i;

	i = 0;
	while (token_array[i] != END_ARRAY)
	{
		if (is_redirect(token_array[i]) && token_array[i + 1] != WORD)
			return (false);
		i++;
	}
	return (true);
}
