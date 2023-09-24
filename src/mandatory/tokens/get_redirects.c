/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:17:38 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 12:33:49 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_redirect_value(t_fd *fd, t_list *last_redirect);

void	get_redirects(t_minishell *minishell)
{
	t_list	*tokens;
	t_list	*last_redirect_in;
	t_list	*last_redirect_out;
	t_token	*token;

	tokens = minishell->tokens;
	last_redirect_in = NULL;
	last_redirect_out = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == REDIRECT_IN || token->type == HEREDOC_IN)
			last_redirect_in = tokens;
		else if (token->type == REDIRECT_OUT || token->type == HEREDOC_OUT)
			last_redirect_out = tokens;
		tokens = tokens->next;
	}
	if (last_redirect_in != NULL)
		get_redirect_value(&minishell->fds.fd_in, last_redirect_in);
	if (last_redirect_out != NULL)
		get_redirect_value(&minishell->fds.fd_out, last_redirect_out);
}

static void	get_redirect_value(t_fd *fd, t_list *last_redirect)
{
	t_token	*token;

	token = last_redirect->content;
	fd->type = token->type;
	last_redirect = last_redirect->next;
	token = last_redirect->content;
	fd->redirect_to = ft_strdup(token->value);
}
