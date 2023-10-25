/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:52:06 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/25 20:38:10 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	handle_sig_child(int sig);

static void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	getset_mini(NULL)->exit_status = CTRLC_RETURN;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigpipe(int sig)
{
	(void)sig;
}

static void	handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	handle_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, handle_sigpipe);
	signal(SIGINT, handle_sigint);
}

void	handle_signal_child(void)
{
	signal(SIGPIPE, handle_sigpipe);
	signal(SIGINT, handle_sig_child);
	signal(SIGQUIT, handle_sig_child);
}
