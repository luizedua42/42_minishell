/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:20:27 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/26 21:37:13 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_expantion(char *value, t_token *token);
static bool	parse_word(char *value, t_token *token);
static bool	special_mode(char *value, size_t *i, char quote);

bool	new_token(t_list **tokens, t_token_type type, char *value,
		size_t *index)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	if (type == EXPANTION)
		parse_expantion(value, token);
	else if (type == WORD)
	{
		if (parse_word(value, token) == false)
			return (false);
	}
	else
		token->value = ft_strdup(value);
	*index += ft_strlen(token->value);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (true);
}

static void	parse_expantion(char *value, t_token *token)
{
	size_t	i;

	i = 0;
	if (value[i] == '&')
		i++;
	while (value[i] != '\0' && !is_space(value[i]) && !is_token(value[i]))
		i++;
	token->value = ft_calloc(i + 1, sizeof(char));
	while (i--)
		token->value[i] = value[i];
}

static bool	parse_word(char *value, t_token *token)
{
	size_t	i;

	i = 0;
	if (value[i] == '&')
		i++;
	while (true)
	{
		while (value[i] != '\0' && !is_space(value[i]) && \
			!is_token(value[i]) && value[i] != '\'' && value[i] != '"')
			i++;
		if (value[i] != '\'' && value[i] != '"')
			break ;
		if (special_mode(value, &i, value[i]) == false)
			return (false);
	}
	token->value = ft_calloc(i + 1, sizeof(char));
	while (i--)
		token->value[i] = value[i];
	return (true);
}

static bool	special_mode(char *value, size_t *i, char quote)
{
	(*i)++;
	while (value[*i] != quote && value[*i] != '\0')
		(*i)++;
	if (value[*i] == '\0')
	{
		ft_fprintf(2, "minishell: syntax error\n");
		return (false);
	}
	(*i)++;
	return (true);
}
