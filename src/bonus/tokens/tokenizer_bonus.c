/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 20:48:19 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static bool	is_double_token(t_list **tokens, char *command, size_t *i);
static bool	is_single_token(t_list **tokens, char *command, size_t *i);

bool	create_tokens(t_list **tokens, char *cmd)
{
	size_t	i;

	i = 0;
	*tokens = NULL;
	while (cmd[i] != '\0')
	{
		if (is_space(cmd[i]))
			i++;
		else if (is_double_token(tokens, cmd, &i))
			continue ;
		else if (is_single_token(tokens, cmd, &i))
			continue ;
		else if (new_token(tokens, WORD, cmd + i, &i) == false)
			return (false);
	}
	if (tokens == NULL)
		return (false);
	return (true);
}

static bool	is_double_token(t_list **tokens, char *command, size_t *i)
{
	if (ft_strncmp("||", command + *i, 2) == 0)
		return (new_token(tokens, OR, "||", i));
	else if (ft_strncmp("&&", command + *i, 2) == 0)
		return (new_token(tokens, AND, "&&", i));
	else if (ft_strncmp("<<", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_IN, "<<", i));
	else if (ft_strncmp(">>", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_OUT, ">>", i));
	return (false);
}

static bool	is_single_token(t_list **tokens, char *command, size_t *i)
{
	if (command[*i] == '|')
		return (new_token(tokens, PIPE, "|", i));
	else if (command[*i] == '<')
		return (new_token(tokens, REDIRECT_IN, "<", i));
	else if (command[*i] == '>')
		return (new_token(tokens, REDIRECT_OUT, ">", i));
	else if (command[*i] == '(')
		return (new_token(tokens, OPEN_PARENTHESIS, "(", i));
	else if (command[*i] == ')')
		return (new_token(tokens, CLOSE_PARENTHESIS, ")", i));
	return (false);
}
