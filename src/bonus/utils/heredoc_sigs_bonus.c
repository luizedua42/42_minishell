/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_sigs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:07:17 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 21:53:08 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	sig_here(int sig)
{
	(void)sig;
	close(getset_fd(-1));
	free(getset_filename(NULL));
	clear_shell(getset_mini(NULL));
	exit(130);
}

void	signal_handler_child_heredoc(void)
{
	signal(SIGINT, sig_here);
	signal(SIGQUIT, SIG_IGN);
}
