/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:01:13 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/11 19:59:43 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_put_in(char *limiter, int *pipedes);
static char *expand_redirect(t_minishell *minishell, char *redirect_to);

void				here_doc(t_minishell *minishell, t_fd *fd)
{
	int		pipedes[2];
	pid_t	pid;

	if (pipe(pipedes) == -1)
	{
		perror(NULL);
		exit(errno);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		exit(errno);
	}
	if (!pid)
	{
		fd->redirect_to = expand_redirect(minishell, fd->redirect_to);
		here_doc_put_in(fd->redirect_to, pipedes);
	}
	else
	{
		close(pipedes[1]);
		dup2(pipedes[0], STDIN_FILENO);
		wait(NULL);
	}
}

static void	here_doc_put_in(char *limiter, int *pipedes)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	close(pipedes[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, limiter_len) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, pipedes[1]);
		free(line);
	}
}

static char *expand_redirect(t_minishell *minishell, char *redirect_to)
{
	char	*expanded_redirect;

	expanded_redirect = expand(minishell, redirect_to, false);
	free(redirect_to);
	return (expanded_redirect);
}
