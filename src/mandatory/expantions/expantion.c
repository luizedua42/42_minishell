/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 00:41:27 by cobli             #+#    #+#             */
/*   Updated: 2023/10/24 16:02:10 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_word(t_list **words, char *str, size_t *index,
				bool is_in_quotes);

char	*expand(t_minishell *minishell, char *str, bool is_in_quotes)
{
	size_t	i;
	t_list	*words;

	i = 0;
	words = NULL;
	while (str[i] != '\0')
	{
		if (!is_in_quotes && str[i] == '"')
			parse_quote(minishell, &words, str + i, &i);
		else if (!is_in_quotes && str[i] == '\'')
			parse_quote(minishell, &words, str + i, &i);
		else if (str[i] == '$')
			parse_env(minishell, &words, str + i, &i);
		else
			parse_word(&words, str + i, &i, is_in_quotes);
	}
	return (join_words(words));
}

static void	parse_word(t_list **words, char *str, size_t *index,
		bool is_in_quotes)
{
	size_t	i;
	char	*word;

	i = 0;
	while (str[i] != '\0' && str[i] != '$' && (is_in_quotes || (str[i] != '\''
				&& str[i] != '"')))
		i++;
	word = calloc(i + 1, sizeof(char));
	ft_strlcpy(word, str, i + 1);
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i;
}

bool	expand_all(t_minishell *minishell, t_list *tokens)
{
	t_token	*token;
	char	*tokenex;

	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == WORD)
		{
			tokenex = expand(minishell, token->value, false);
			free(token->value);
			token->value = tokenex;
		}
		tokens = tokens->next;
	}
	if (open_here_docs(minishell, minishell->tokens) == false)
		return (false);
	return (true);
}
