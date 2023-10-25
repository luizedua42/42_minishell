/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 06:01:13 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/25 16:38:41 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	here_doc_put_in(t_minishell *minishell, char *limiter, int fd);
static char	*expand_line(char *line, t_minishell *minishell);
static void	parse_line(t_list **words, char *str, size_t *index);
static void	parse_here_env(t_minishell *minishell, t_list **words, char *str,
							size_t *index);

void	here_doc(t_minishell *minishell, t_token *fds, char *index)
{
	int		fd;
	char	*file_name;

	file_name = ft_strjoin("/tmp/mini_doc_", index);
	getset_filename(file_name);
	free(index);
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	getset_fd(fd);
	here_doc_put_in(minishell, fds->value, fd);
	free(file_name);
	close(fd);
}

static void	here_doc_put_in(t_minishell *minishell, char *limiter, int fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, limiter, limiter_len + 1) == 0)
			return (heredoc_err(line, limiter, limiter_len));
		if (line[0] != '\0')
			line = expand_line(line, minishell);
		if (line == NULL)
		{
			ft_putendl_fd("", fd);
			continue ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static char	*expand_line(char *line, t_minishell *minishell)
{
	size_t	i;
	t_list	*words;

	i = 0;
	words = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			parse_here_env(minishell, &words, line + i, &i);
		else
			parse_line(&words, line + i, &i);
	}
	free(line);
	return (join_words(words));
}

static void	parse_here_env(t_minishell *minishell, t_list **words, char *str,
		size_t *index)
{
	size_t	i;
	char	*word;

	i = 1;
	if (str[i] == '?' || ft_isdigit(str[i]))
	{
		if (str[i] == '0')
			ft_lstadd_back(words, ft_lstnew(ft_strdup("minishell")));
		if (str[i] == '?')
			ft_lstadd_back(words, ft_lstnew(ft_itoa(minishell->exit_status)));
		*index += i + 1;
		return ;
	}
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 1)
		word = ft_strdup("$");
	else
		expand_env(i, str, &word, minishell->envs);
	if (word == NULL)
		word = ft_strdup("");
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i;
}

static void	parse_line(t_list **words, char *str, size_t *index)
{
	size_t	i;
	char	*word;

	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	word = calloc(i + 1, sizeof(char));
	ft_strlcpy(word, str, i + 1);
	ft_lstadd_back(words, ft_lstnew(word));
	*index += i;
}
