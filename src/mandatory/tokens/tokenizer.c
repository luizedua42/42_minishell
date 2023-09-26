/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:48:19 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/25 22:53:18 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_double_token(t_list **tokens, char *command, size_t *i);
static bool	is_single_token(t_list **tokens, char *command, size_t *i);
static bool	quote_parse(t_list **tokens, char *command, size_t *i, char quote);

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
		else if (command[i] == '\'' || command[i] == '"')
		{
			i++;
			if (quote_parse(&tokens, command + i, &i, command[i - 1]) == false)
				return (NULL);
		}
		else if (is_double_token(&tokens, command, &i))
			continue ;
		else if (is_single_token(&tokens, command, &i))
			continue ;
		else if (is_builtin(&tokens, command, &i))
			continue ;
		else if (new_token(&tokens, WORD, command + i, &i) == false)
			break ;
	}
	return (tokens);
}

static bool	quote_parse(t_list **tokens, char *command, size_t *i, char quote)
{
	size_t	index;
	t_token	*token;

	index = 0;
	token = ft_calloc(1, sizeof(t_token));
	if (quote == '\'')
		token->type = QUOTE;
	else
		token->type = DQUOTE;
	while (command[index] != quote && command[index] != '\0')
		index++;
	if (command[index] == '\0')
	{
		ft_fprintf(2, "minishell: syntax error\n");
		return (false);
	}
	command[index] = '\0';
	token->value = ft_strdup(command);
	*i += index + 1;
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
	else if (command[*i] == '$' && !ft_isspace(command[*i + 1]))
		return (new_token(tokens, EXPANTION, command + (*i), i));
	else if (command[*i] == '(')
		return (new_token(tokens, OPEN_PARENTHESIS, "(", i));
	else if (command[*i] == ')')
		return (new_token(tokens, CLOSE_PARENTHESIS, ")", i));
	return (false);
}
