/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:17:38 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/25 16:17:43 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	*get_redirect_value(t_list **token_lst);

t_list	*get_redirects(t_list *tokens)
{
	t_list	*fds;
	t_token	*token;

	fds = NULL;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (is_redirect(token->type))
			ft_lstadd_back(&fds, ft_lstnew(get_redirect_value(&tokens)));
		tokens = tokens->next;
	}
	return (fds);
}

static t_fd	*get_redirect_value(t_list **token_lst)
{
	t_token	*token;
	t_fd	*fd;

	fd = ft_calloc(1, sizeof(t_fd));
	token = (*token_lst)->content;
	fd->type = token->type;
	(*token_lst) = (*token_lst)->next;
	token = (*token_lst)->content;
	fd->redirect_to = ft_strdup(token->value);
	fd->fd = -1;
	return (fd);
}
