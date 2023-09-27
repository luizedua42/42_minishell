/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:14:10 by cobli             #+#    #+#             */
/*   Updated: 2023/09/26 21:37:47 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_exe(t_token_type type)
{
	return (type == WORD || type == BUILTIN || type == DQUOTE \
				|| type == QUOTE || is_redirect(type));
}
