/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:18:32 by luizedua          #+#    #+#             */
/*   Updated: 2023/08/30 19:51:03 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env_built(char **envp)
{
	int	i;

	i = 0;
	while(envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (0);
	env_built(envp);
	return (0);
}