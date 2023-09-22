/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:43:31 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/22 00:58:01 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **args, t_list *envs)
{
	int		ret;
	size_t	argc;
	char	*path;

	argc = count_args(args);
	path = args[1];
	if (argc == 1)
	{
		path = find_env_value(envs, "HOME");
		if (path == NULL)
		{
			ft_fprintf(2, "minishell: cd: HOME not defined\n");
			return ;
		}
	}
	else if (argc != 2)
	{
		ft_fprintf(2, "minishell: cd: too many arguments\n");
		return ;
	}
	ret = chdir(path);
	if (ret < 0)
		return (perror("minishell: cd"));
}
