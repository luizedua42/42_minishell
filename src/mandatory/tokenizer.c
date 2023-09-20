/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:48:19 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/20 14:14:36 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_token(char c)
{
	return (c == '\'' || c == '\"' || c == '|' || c == '&' || c == '<' || \
			c == '>' || c == '$' || c == '(' || c == ')');
}

static bool	new_token(t_list **tokens, t_token_type type, char *value,
	size_t *index)
{
	size_t	i;
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	if (type == WORD)
	{
		i = 0;
		while (value[i] != '\0' && !ft_isspace(value[i]) && !is_token(value[i]))
			i++;
		token->value = ft_calloc(i + 1, sizeof(char));
		while (i--)
			token->value[i] = value[i];
	}
	else
		token->value = ft_strdup(value);
	*index += ft_strlen(token->value);
	ft_lstadd_back(tokens, ft_lstnew(token));
	return (true);
}

static bool	is_double_token(t_list **tokens, char *command, size_t *i)
{
	if (ft_strncmp("||", command + *i, 2) == 0)
		return (new_token(tokens, OR, "||", i));
	else if (ft_strncmp("&&", command + *i, 2) == 0)
		return (new_token(tokens, AND, "&&", i));
	else if (ft_strncmp("<<", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_IN, "<<", i));
	else if (ft_strncmp(">>", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_OUT, ">>", i));
	return (false);
}

static bool	is_single_token(t_list **tokens, char *command, size_t *i)
{
	if (command[*i] == '|')
		return (new_token(tokens, PIPE, "|", i));
	else if (command[*i] == '<')
		return (new_token(tokens, REDIRECT_IN, "<", i));
	else if (command[*i] == '>')
		return (new_token(tokens, REDIRECT_OUT, ">", i));
	else if (command[*i] == '\'')
		return (new_token(tokens, QUOTE, "'", i));
	else if (command[*i] == '\"')
		return (new_token(tokens, DQUOTE, "\"", i));
	else if (command[*i] == '$')
		return (new_token(tokens, DOLLAR_SIGN, "$", i));
	else if (command[*i] == '(')
		return (new_token(tokens, OPEN_PARENTHESIS, "(", i));
	else if (command[*i] == ')')
		return (new_token(tokens, CLOSE_PARENTHESIS, ")", i));
	return (false);
}

t_list	*create_tokens(char *command)
{
	t_list	*tokens;
	size_t	i;

	i = 0;
	tokens = NULL;
	while (command[i] != '\0')
	{
		if (ft_isspace(command[i]))
			i++;
		else if (is_double_token(&tokens, command, &i))
			continue ;
		else if (is_single_token(&tokens, command, &i))
			continue ;
		else
			new_token(&tokens, WORD, command + i, &i);
	}
	return (tokens);
}
