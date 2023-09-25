/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:41:08 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 16:37:35 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_envs(t_env **envs);
static void	print_sorted_envs(t_minishell *minishell);

int	minishell_export(t_minishell *minishell, char **args)
{
	size_t	argc;

	argc = count_args(args);
	if (argc == 1)
		print_sorted_envs(minishell);
	return (EXIT_SUCCESS);
}

static void	sort_envs(t_env **envs)
{
	size_t	i;
	size_t	j;
	size_t	size;

	size = 0;
	while (envs[size] != NULL)
		size++;
	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(envs[i]->key, envs[j]->key) > 0)
				ft_pswap((void **)(&envs[i]), (void **)(&envs[j]));
			j++;
		}
		i++;
	}
}

static void	print_sorted_envs(t_minishell *minishell)
{
	size_t	i;
	t_env	**envs;

	i = 0;
	envs = (t_env **)ft_lst_to_array(minishell->envs);
	sort_envs(envs);
	while (envs[i] != NULL)
	{
		if (envs[i]->value == NULL)
			ft_printf("export -x %s\n", envs[i]->key);
		else
			ft_printf("export -x %s=\"%s\"\n", envs[i]->key, envs[i]->value);
		i++;
	}
	free(envs);
}
