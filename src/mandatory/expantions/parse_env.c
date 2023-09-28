/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:32:47 by cobli             #+#    #+#             */
/*   Updated: 2023/09/28 08:53:28 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_minishell *minishell, t_list **words, char *str,
		size_t *index)
{
	size_t	i;
	char	*key;
	char	*word;
	char	*env_value;

	i = 1;
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '"'
		&& !is_space(str[i]))
		i++;
	if (i == 1)
		word = ft_strdup("$");
	else
	{
		key = calloc(i, sizeof(char));
		ft_strlcpy(key, str + 1, i);
		env_value = find_env_value(minishell->envs, key);
		if (env_value == NULL)
			word = ft_strdup("");
		else
			word = ft_strdup(env_value);
		free(key);
	}
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i;
}
