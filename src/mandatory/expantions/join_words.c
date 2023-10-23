/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:34:06 by cobli             #+#    #+#             */
/*   Updated: 2023/10/21 20:10:48 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_words(t_list *words);

char	*join_words(t_list *words)
{
	char	*str;
	char	*aux;
	t_list	*head;

	if (words == NULL)
		return (NULL);
	head = words;
	if (check_words(words) == false)
		return (NULL);
	str = ft_strdup("");
	while (words != NULL)
	{
		if (words->content == NULL)
		{
			words = words->next;
			continue ;
		}
		aux = ft_strjoin(str, (char *)words->content);
		free(str);
		str = aux;
		words = words->next;
	}
	ft_lstclear(&head, free);
	return (str);
}

static bool	check_words(t_list *words)
{
	t_list	*head;

	head = words;
	while (words != NULL)
	{
		if (words->content != NULL)
		{
			return (true);
		}
		words = words->next;
	}
	ft_lstclear(&head, free);
	return (false);
}
