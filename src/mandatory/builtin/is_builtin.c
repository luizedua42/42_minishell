/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:18:44 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 20:59:35 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_list **tokens, char *command, size_t *i)
{
	if (ft_strncmp("cd", command + *i, 2) == 0)
		return (new_token(tokens, BUILTIN, "cd", i));
	else if (ft_strncmp("env", command + *i, 3) == 0)
		return (new_token(tokens, BUILTIN, "env", i));
	else if (ft_strncmp("pwd", command + *i, 3) == 0)
		return (new_token(tokens, BUILTIN, "pwd", i));
	else if (ft_strncmp("export", command + *i, 6) == 0)
		return (new_token(tokens, BUILTIN, "export", i));
	else if (ft_strncmp("unset", command + *i, 5) == 0)
		return (new_token(tokens, BUILTIN, "unset", i));
	else if (ft_strncmp("exit", command + *i, 4) == 0)
		return (new_token(tokens, BUILTIN, "exit", i));
	else if (ft_strncmp("echo", command + *i, 4) == 0)
		return (new_token(tokens, BUILTIN, "echo", i));
	return (false);
}
