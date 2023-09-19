/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/19 13:11:00 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_token(char c)
{
	return (c == '\'' || c == '\"');
}

bool	token_cmp(char *source, char *cmp)
{
	while (*source != '\0')
		if (*source++ != *cmp++)
			return (false);
	return (*cmp == '\0' || *cmp == ' ');
}

void	new_token(t_list **tokens, t_token_type type, char *value,
		size_t *index)
{
	size_t	i;
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	if (type == WORD)
	{
		i = 0;
		while (value[i] != '\0' && value[i] != ' ' && !is_token(value[i]))
			i++;
		token->value = ft_calloc(i + 1, sizeof(char));
		while (i--)
			token->value[i] = value[i];
	}
	else
		token->value = ft_strdup(value);
	*index += ft_strlen(token->value);
	ft_lstadd_back(tokens, ft_lstnew(token));
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
		else if (token_cmp("||", command + i))
			new_token(&tokens, OR, "||", &i);
		else if (token_cmp("|", command + i))
			new_token(&tokens, PIPE, "|", &i);
		else if (token_cmp("&&", command + i))
			new_token(&tokens, AND, "&&", &i);
		else if (token_cmp("<", command + i))
			new_token(&tokens, REDIRECT_IN, "<", &i);
		else if (token_cmp(">", command + i))
			new_token(&tokens, REDIRECT_OUT, ">", &i);
		else if (token_cmp("<<", command + i))
			new_token(&tokens, HEREDOC_IN, "<<", &i);
		else if (token_cmp(">>", command + i))
			new_token(&tokens, HEREDOC_OUT, ">>", &i);
		else if (command[i] == '\'')
			new_token(&tokens, QUOTE, "'", &i);
		else if (command[i] == '\"')
			new_token(&tokens, DQUOTE, "\"", &i);
		else if (command[i] == '$')
			new_token(&tokens, DOLLAR_SIGN, "$", &i);
		else if (command[i] == '(')
			new_token(&tokens, OPEN_PARENTHESIS, "(", &i);
		else if (command[i] == ')')
			new_token(&tokens, CLOSE_PARENTHESIS, ")", &i);
		else
			new_token(&tokens, WORD, command + i, &i);
	}
	return (tokens);
}

int	main(int argc, char **argv)
{
	t_list	*tokens;
	t_token	*teste;
	char	*command;
	char	*prompt;

	if (argc != 2)
		return (1);
	(void)argv;
	while (1)
	{
		prompt = "minishell$ ";
		command = readline(prompt);
		tokens = create_tokens(command);
		while (tokens != NULL)
		{
			teste = (t_token *)(tokens->content);
			ft_printf("%s\n", teste->value);
			tokens = tokens->next;
		}
	}
	return (0);
}
