/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:44:42 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/25 22:55:24 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(t_token_type type)
{
	return (type == AND || type == OR || type == PIPE);
}
