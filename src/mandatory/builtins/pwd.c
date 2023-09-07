/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:58:54 by luizedua          #+#    #+#             */
/*   Updated: 2023/08/30 19:50:53 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	pwd_built(void)
{
	char	*path;

	path = malloc(PATH_MAX * sizeof(char));
	if (!path)
	{
		perror("pwd: ");
		return;
	}
	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("pwd: ");
		return;
	}
	printf("%s\n", path);
	free(path);
}

int main(void)
{
	pwd_built();
	return (0);
}
