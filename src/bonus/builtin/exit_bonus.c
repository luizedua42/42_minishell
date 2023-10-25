/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:57:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/25 15:35:11 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int					free_all(t_minishell *minishell, int ret);
static unsigned long long	ft_atoull(const char *nptr);

int	minishell_exit(t_minishell *minishell, char **args, bool has_pipe)
{
	unsigned long long	ret;

	ret = minishell->exit_status;
	if (!has_pipe)
		ft_printf("exit\n");
	if (args[1] != NULL)
		ret = ft_atoull(args[1]);
	if (ret == (unsigned long long)LLONG_MAX + 2)
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
	if (has_pipe)
		return (ret);
	return (free_all(minishell, ret));
}

static int	free_all(t_minishell *minishell, int ret)
{
	rl_clear_history();
	clear_shell(minishell);
	return (ret);
}

static unsigned long long	ft_atoull(const char *nptr)
{
	int					f;
	unsigned long long	n;

	f = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+')
		f = 1;
	else if (*nptr == '-')
		f = -1;
	if (f)
		nptr++;
	n = 0;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		if ((f != -1 && n > LLONG_MAX) || n > (unsigned long long)LLONG_MAX + 1)
			return ((unsigned long long)LLONG_MAX + 2);
		nptr++;
	}
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr != '\0')
		return ((unsigned long long)LLONG_MAX + 2);
	return (n);
}
