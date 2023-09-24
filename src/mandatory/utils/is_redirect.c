/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:47:52 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 11:49:24 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token *token)
{
	return (token->type == REDIRECT_IN || token->type == REDIRECT_OUT
		|| token->type == HEREDOC_IN || token->type == HEREDOC_OUT);
}
