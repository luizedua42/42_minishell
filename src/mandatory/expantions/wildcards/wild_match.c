/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:25:23 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/21 01:45:33 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	wild_match(const char *pattern, const char *string)
{
	if (*pattern == '\0' && *string == '\0')
		return (true);
	if (*pattern == '*')
	{
		while (*string != '\0')
		{
			if (wild_match(pattern + 1, string))
				return (true);
			string++;
		}
		return (wild_match(pattern + 1, string));
	}
	if (*pattern == *string)
		return (wild_match(pattern + 1, string + 1));
	return (false);
}
