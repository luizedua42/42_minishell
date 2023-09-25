/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:47:52 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 23:23:19 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token_type type)
{
	return (type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC_IN
		|| type == HEREDOC_OUT);
}
