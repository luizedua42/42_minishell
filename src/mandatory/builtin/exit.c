/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:57:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/17 20:58:57 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_num_arg(char *arg);
static int	free_all(t_minishell *minishell, int ret);

int	minishell_exit(t_minishell *minishell, char **args, bool has_pipe)
{
	int	ret;

	ret = minishell->exit_status;
	if (!has_pipe)
		ft_printf("exit\n");
	if (args[1] != NULL && is_num_arg(args[1]) == false)
	{
		ft_fprintf(STDERR_FILENO, \
			"minishell: exit: %s: numeric argument required\n", args[1]);
		return (free_all(minishell, 2));
	}
	if (count_args(args) > 2)
	{
		ft_fprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		if (has_pipe)
			return (EXIT_FAILURE);
		return (-2);
	}
	if (args[1] != NULL)
		ret = ft_atoi(args[1]);
	if (has_pipe)
		return (ret);
	return (free_all(minishell, ret));
}

static bool	is_num_arg(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] == '\0')
		return (false);
	while (arg[i] != '\0')
	{
		if (!isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	free_all(t_minishell *minishell, int ret)
{
	rl_clear_history();
	clear_shell(minishell);
	return (ret);
}
