/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:57:09 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/24 12:21:01 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*create_node(t_token_type type, char *value);

t_tree	*create_tree(t_list *tokens)
{
	t_tree	*tree;
	t_tree	*head;
	t_token	*token;

	tree = NULL;
	token = tokens->content;
	tree = ft_newnode(create_node(token->type, token->value));
	head = tree;
	tokens = tokens->next;
	while (tokens != NULL)
	{
		token = tokens->content;
		tree->right = ft_newnode(create_node(token->type, token->value));
		tree = tree->right;
		tokens = tokens->next;
	}
	return (head);
}

static t_node	*create_node(t_token_type type, char *value)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->type = type;
	node->value = ft_strdup(value);
	return (node);
}
