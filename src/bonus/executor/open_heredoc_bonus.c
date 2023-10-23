/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:02:07 by luizedua          #+#    #+#             */
/*   Updated: 2023/10/22 22:51:27 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static size_t	count_here_docs(t_list *tokens);
static void		get_here_docs_files(t_list *tokens);
static void		here_child(t_minishell *minishell, t_list *tokens);

bool	open_here_docs(t_minishell *minishell, t_list *tokens)
{
	int		pid;
	int		status;

	if (count_here_docs(tokens) > 0)
	{
		pid = fork();
		if (pid == 0)
			here_child(minishell, tokens);
		waitpid(pid, &status, 0);
		get_here_docs_files(minishell->tokens);
		if (WEXITSTATUS(status) == 130)
			return (false);
	}
	return (true);
}

static size_t	count_here_docs(t_list *tokens)
{
	size_t	count;
	t_token	*token;

	count = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == HEREDOC_IN)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	get_here_docs_files(t_list *tokens)
{
	t_token	*token;
	int		count;
	char	*file_name;
	char	*index;

	count = 0;
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == HEREDOC_IN)
		{
			tokens = tokens->next;
			token = tokens->content;
			index = ft_itoa(count);
			file_name = ft_strjoin("/tmp/mini_doc_", index);
			free(index);
			free(token->value);
			token->value = ft_strdup(file_name);
			free(file_name);
			count++;
		}
		tokens = tokens->next;
	}
}

static void	here_child(t_minishell *minishell, t_list *tokens)
{
	int		index;
	t_token	*token;

	index = 0;
	getset_mini(minishell);
	signal_handler_child_heredoc();
	while (tokens != NULL)
	{
		token = tokens->content;
		if (token->type == HEREDOC_IN)
		{
			tokens = tokens->next;
			token = tokens->content;
			here_doc(minishell, token, ft_itoa(index));
			index++;
		}
		tokens = tokens->next;
	}
	clear_shell(minishell);
	exit(0);
}

void	heredoc_err(char *line, char *limiter, size_t limiter_len)
{
	if (ft_strncmp(line, limiter, limiter_len + 1) == 0)
		return (free(line));
	write(2, "minishell: warning: here-document delimited by" \
		" end-of-file (wanted `", 68);
	write(2, limiter, limiter_len);
	write(2, "')\n", 3);
	return (free(line));
}
