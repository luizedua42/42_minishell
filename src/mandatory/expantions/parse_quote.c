/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:36:43 by cobli             #+#    #+#             */
/*   Updated: 2023/10/25 16:09:20 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_quote(t_minishell *minishell, t_list **words, char *str,
		size_t *index)
{
	size_t	i;
	char	*word;
	char	*aux;
	char	quote;

	i = 1;
	quote = str[0];
	while (str[i] != quote)
		i++;
	if (i == 1)
		word = ft_strdup("");
	else
	{
		word = calloc(i, sizeof(char));
		ft_strlcpy(word, str + 1, i);
		if (quote == '"' && ft_strchr(word, '$') != NULL)
		{
			aux = expand(minishell, word, true);
			free(word);
			word = aux;
		}
	}
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i + 1;
}
