/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:44:28 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/03 16:45:58 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(void)
{
	char	*usr;

	usr = "\001\x1b[32m\002cadet@minishell\001\x1b[m\002:" \
		"\001\x1b[34m\002~\001\x1b[m\002\001\x1b[37m\002$\001\x1b[m\002 ";
	return (usr);
}
