/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:49:21 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/16 20:50:44 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (ft_strncmp("cd", cmd, 2) == 0)
		return (true);
	else if (ft_strncmp("env", cmd, 3) == 0)
		return (true);
	else if (ft_strncmp("pwd", cmd, 3) == 0)
		return (true);
	else if (ft_strncmp("export", cmd, 6) == 0)
		return (true);
	else if (ft_strncmp("unset", cmd, 5) == 0)
		return (true);
	else if (ft_strncmp("exit", cmd, 4) == 0)
		return (true);
	else if (ft_strncmp("echo", cmd, 4) == 0)
		return (true);
	return (false);
}
