/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:28:36 by luizedua          #+#    #+#             */
/*   Updated: 2023/05/18 16:42:02 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	index;
	size_t	words;

	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		if (s[index] != c && s[index] != '\0')
			words++;
		while (s[index] != c && s[index] != '\0')
			index++;
	}
	return (words);
}

static int	free_all(char **bfree)
{
	char	**tmp;

	tmp = bfree;
	while (!bfree)
	{
		free(*bfree);
		bfree++;
	}
	free(tmp);
	return (1);
}

static void	alloc_words(char const *s, char c, char **array)
{
	size_t	index;
	size_t	old_index;
	size_t	count_array;
	size_t	words;

	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
		while (s[index] == c)
			index++;
		if (s[index] != c && s[index] != '\0')
			old_index = index;
		count_array = 0;
		while (s[index] != c && s[index] != '\0')
		{
			count_array++;
			index++;
		}
		if (count_array != 0)
			array[words++] = ft_substr(&s[old_index], 0, count_array);
		if (words > 0 && array[words - 1] == NULL && free_all(array))
			return ;
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**array;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	array = (char **)ft_calloc((words + 1), sizeof(char *));
	if (array == NULL)
		return (NULL);
	alloc_words(s, c, array);
	return (array);
}
