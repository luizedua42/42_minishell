/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:41:08 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void		sort_envs(t_env **envs);
static bool		check_parameter(char *str);
static void		print_sorted_envs(t_minishell *minishell);
static size_t	handle_envs(t_minishell *minishell, char **args);

int	minishell_export(t_minishell *minishell, char **args)
{
	size_t	argc;
	size_t	valid_args;

	argc = count_args(args);
	valid_args = 0;
	if (argc == 1)
		print_sorted_envs(minishell);
	else
		valid_args = handle_envs(minishell, args + 1);
	if (valid_args < argc - 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static size_t	handle_envs(t_minishell *minishell, char **args)
{
	size_t	i;
	char	*key;
	char	*value;
	size_t	valid_args;
	bool	is_valid_args;

	i = 0;
	valid_args = 0;
	while (args[i] != NULL)
	{
		key = args[i];
		value = ft_strchr(args[i], '=');
		if (value != NULL)
		{
			*value = '\0';
			value++;
		}
		is_valid_args = check_parameter(args[i++]);
		valid_args += is_valid_args;
		if (!is_valid_args)
			continue ;
		export_env(minishell, key, value);
	}
	return (valid_args);
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
			ft_printf("declare -x %s\n", envs[i]->key);
		else
			ft_printf("declare -x %s=\"%s\"\n", envs[i]->key, envs[i]->value);
		i++;
	}
	free(envs);
}

static bool	check_parameter(char *str)
{
	size_t	i;
	bool	is_valid;

	i = 0;
	is_valid = true;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			is_valid = false;
			break ;
		}
		i++;
	}
	if (ft_isdigit(str[0]) || str[0] == '=' || !is_valid || str[0] == '\0')
	{
		ft_fprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", str);
		return (false);
	}
	return (true);
}
