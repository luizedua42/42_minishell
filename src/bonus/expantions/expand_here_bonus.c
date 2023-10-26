/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:00:51 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/25 22:02:55 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	parse_word_here(t_list **words, char *str, size_t *index,
				bool is_in_quotes);

char	*expand_here(char *str, bool is_in_quotes)
{
	size_t	i;
	t_list	*words;

	i = 0;
	words = NULL;
	while (str[i] != '\0')
	{
		if (!is_in_quotes && str[i] == '"')
			parse_quote_here(&words, str + i, &i);
		else if (!is_in_quotes && str[i] == '\'')
			parse_quote_here(&words, str + i, &i);
		else
			parse_word_here(&words, str + i, &i, is_in_quotes);
	}
	return (join_words(words));
}

static void	parse_word_here(t_list **words, char *str, size_t *index,
		bool is_in_quotes)
{
	size_t	i;
	char	*word;

	i = 0;
	while (str[i] != '\0' && (is_in_quotes || (str[i] != '\'' \
				&& str[i] != '"')))
		i++;
	word = calloc(i + 1, sizeof(char));
	ft_strlcpy(word, str, i + 1);
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i;
}
