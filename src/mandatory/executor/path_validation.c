/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 23:35:01 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/23 23:37:54 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	path_validation(char *cmd)
{
	return (ft_strchr(cmd, '/') == NULL && \
		ft_strncmp(cmd, "..", 3) != 0 && ft_strncmp(cmd, ".", 2) != 0 \
			&& cmd[0] != '\0');
}
