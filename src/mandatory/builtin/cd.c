/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:43:31 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 22:17:41 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **args)
{
	int	ret;

	if (count_args(args) != 2)
	{
		ft_fprintf(2, "cd : too many arguments\n");
		return ;
	}
	ret = chdir(args[1]);
	if (ret < 0)
		return (perror("cd "));
}
