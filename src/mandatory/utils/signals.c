/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:52:06 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/17 22:47:28 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint_child(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
}

void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_signal_child(void)
{
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, SIG_IGN);
}
