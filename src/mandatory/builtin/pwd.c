/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:38:52 by luizedua          #+#    #+#             */
/*   Updated: 2023/09/21 21:41:02 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*path;

	path = ft_calloc(PATH_MAX, sizeof(char));
	if (!path)
		return (perror("pwd: "));
	if (getcwd(path, PATH_MAX) == NULL)
		return (perror("pwd: "));
	ft_printf("%s\n", path);
	free(path);
}
