/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:49:21 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/26 01:35:39 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

bool	is_builtin(char *cmd)
{
	if (ft_strncmp("cd", cmd, 3) == 0)
		return (true);
	else if (ft_strncmp("env", cmd, 4) == 0)
		return (true);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		return (true);
	else if (ft_strncmp("export", cmd, 7) == 0)
		return (true);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		return (true);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (true);
	else if (ft_strncmp("echo", cmd, 5) == 0)
		return (true);
	return (false);
}
