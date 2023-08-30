/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:47:13 by luizedua          #+#    #+#             */
/*   Updated: 2023/08/30 20:07:32 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void cd_built(const char *path)
{
	int	ret;

	ret = chdir(path);
	if(ret < 0)
	{
		perror("cd : ");
		return;
	}
}

int	main(void)
{
	char *buf;
	buf = malloc(PATH_MAX * sizeof(char));
	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
	cd_built("../../");
	getcwd(buf, PATH_MAX);
	printf("%s\n", buf);
}