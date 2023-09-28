/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:34:06 by cobli             #+#    #+#             */
/*   Updated: 2023/09/28 08:34:19 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_words(t_list *words)
{
	char	*str;
	char	*aux;
	t_list	*head;

	if (words == NULL)
		return (NULL);
	head = words;
	str = ft_strdup("");
	while (words != NULL)
	{
		aux = ft_strjoin(str, (char *)words->content);
		free(str);
		str = aux;
		words = words->next;
	}
	ft_lstclear(&head, free);
	return (str);
}
