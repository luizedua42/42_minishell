/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 00:41:27 by cobli             #+#    #+#             */
/*   Updated: 2023/10/21 01:33:13 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_word(t_list **words, char *str, size_t *index,
				bool is_in_quotes);
static char	*handle_wild(t_list *words);

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
	return (handle_wild(words));
}

static char	*handle_wild(t_list *words)
{
	char	*aux;
	char	*expantion;
	size_t	i;

	i = 0;
	expantion = join_words(words);
	if (ft_strchr(expantion, '*') != NULL)
	{
		aux = wild_get(expantion);
		if (aux == NULL)
			return (expantion);
		free(expantion);
		expantion = aux;
	}
	while (expantion[i] != '\0')
	{
		if (expantion[i] == -1)
			expantion[i] = '*';
		i++;
	}
	return (expantion);
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

void	expand_all(t_minishell *minishell, t_list *tokens)
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
}
