/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cobli <cobli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:38:52 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/23 02:40:20 by cobli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (perror("pwd: "));
	ft_printf("%s\n", path);
	free(path);
}
