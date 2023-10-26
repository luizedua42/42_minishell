/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 22:57:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/26 00:17:46 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int					free_all(t_minishell *minishell, int ret);
static unsigned long long	ft_atoull(const char *nptr, int *flag);

int	minishell_exit(t_minishell *minishell, char **args, bool has_pipe)
{
	int					flag;
	unsigned long long	ret;

	ret = minishell->exit_status;
	if (!has_pipe)
		ft_printf("exit\n");
	if (args[1] != NULL)
		ret = ft_atoull(args[1], &flag);
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
		return (((int)ret) * flag);
	return (free_all(minishell, ((int)ret) * flag));
}

static int	free_all(t_minishell *minishell, int ret)
{
	rl_clear_history();
	clear_shell(minishell);
	return (ret);
}

static unsigned long long	ft_atoull(const char *nptr, int *flag)
{
	unsigned long long	nb;

	*flag = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		*flag = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	nb = 0;
	while (ft_isdigit(*nptr))
	{
		nb = nb * 10 + (*nptr - '0');
		if ((*flag != -1 && nb > LLONG_MAX) || \
			nb > (unsigned long long)LLONG_MAX + 1)
			return ((unsigned long long)LLONG_MAX + 2);
		nptr++;
	}
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr != '\0')
		return ((unsigned long long)LLONG_MAX + 2);
	return (nb);
}
