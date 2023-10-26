/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_selector_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:18:44 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/25 15:33:03 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	builtin_selector(t_minishell *minishell, char **args, bool has_pipe)
{
	if (ft_strncmp("cd", args[0], 3) == 0)
		return (cd(minishell, args));
	else if (ft_strncmp("env", args[0], 4) == 0)
		return (env(minishell));
	else if (ft_strncmp("pwd", args[0], 4) == 0)
		return (pwd());
	else if (ft_strncmp("export", args[0], 7) == 0)
		return (minishell_export(minishell, args));
	else if (ft_strncmp("unset", args[0], 6) == 0)
		return (unset(minishell, args));
	else if (ft_strncmp("exit", args[0], 5) == 0)
		return (minishell_exit(minishell, args, has_pipe));
	else if (ft_strncmp("echo", args[0], 5) == 0)
		return (echo(args));
	return (-1);
}
