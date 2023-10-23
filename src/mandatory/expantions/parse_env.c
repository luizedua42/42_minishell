/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 08:32:47 by cobli             #+#    #+#             */
/*   Updated: 2023/10/22 21:34:38 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_minishell *minishell, t_list **words, char *str,
		size_t *index)
{
	size_t	i;
	char	*word;

	i = 1;
	if (str[i] == '?' || ft_isdigit(str[i]))
	{
		if (str[i] == '0')
			ft_lstadd_back(words, ft_lstnew(ft_strdup("minishell")));
		if (str[i] == '?')
			ft_lstadd_back(words, ft_lstnew(ft_itoa(minishell->exit_status)));
		*index += i + 1;
		return ;
	}
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '"' \
			&& (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1)
		word = ft_strdup("$");
	else
		expand_env(i, str, &word, minishell->envs);
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i;
}

void	expand_env(size_t i, char *str, char **word, t_list *envs)
{
	char	*key;
	char	*env_value;

	key = calloc(i, sizeof(char));
	ft_strlcpy(key, str + 1, i);
	env_value = find_env_value(envs, key);
	if (env_value == NULL)
		*word = NULL;
	else
		*word = ft_strdup(env_value);
	free(key);
}
