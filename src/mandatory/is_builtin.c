/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:18:44 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 20:07:02 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_list **tokens, char *command, size_t *i)
{
	if (ft_strncmp("cd", command + *i, 2) == 0)
		return (new_token(tokens, OR, "||", i));
	else if (ft_strncmp("env", command + *i, 2) == 0)
		return (new_token(tokens, AND, "&&", i));
	else if (ft_strncmp("pwd", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_IN, "<<", i));
	else if (ft_strncmp("export", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_OUT, ">>", i));
	else if (ft_strncmp("unset", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_OUT, ">>", i));
	else if (ft_strncmp("exit", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_OUT, ">>", i));
	else if (ft_strncmp("echo", command + *i, 2) == 0)
		return (new_token(tokens, HEREDOC_OUT, ">>", i));
	return (false);
}
