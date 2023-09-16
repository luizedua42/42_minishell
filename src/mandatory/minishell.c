/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:07:51 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/16 19:57:50 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	return (token);
}

int	main(int argc, char **argv)
{
	t_list	*tokens;
	t_token	*teste;
	size_t	i;
	char	**commands;

	if (argc != 2)
		return (1);
	i = 0;
	tokens = NULL;
	commands = ft_split(argv[1], ' ');
	while (commands[i])
	{

		if (ft_strncmp("||", commands[i], 2) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(OR, "||")));
		else if (ft_strncmp("|", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(PIPE, "|")));
		else if (ft_strncmp("&&", commands[i], 2) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(AND, "&&")));
		else if (ft_strncmp("<", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(REDIRECT_IN, "<")));
		else if (ft_strncmp(">", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(REDIRECT_OUT, ">")));
		else if (ft_strncmp("<<", commands[i], 2) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(HEREDOC_IN, "<<")));
		else if (ft_strncmp(">>", commands[i], 2) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(HEREDOC_OUT, ">>")));
		else if (ft_strncmp("'", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(QUOTE, "'")));
		else if (ft_strncmp("\"", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(DQUOTE, "\"")));
		else if (ft_strncmp("$", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(DOLLAR_SIGN, "$")));
		else if (ft_strncmp("(", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(OPEN_PARENTHESIS, "(")));
		else if (ft_strncmp(")", commands[i], 1) == 0)
			ft_lstadd_back(&tokens, ft_lstnew(new_token(CLOSE_PARENTHESIS, ")")));
		else
			ft_lstadd_back(&tokens, ft_lstnew(new_token(WORD, commands[i])));
		i++;
	}
	while (tokens != NULL)
	{
		teste = (t_token *)(tokens->content);
		ft_printf("%s\n", teste->value);
		tokens = tokens->next;
	}
	ft_free_split(commands);
	return (0);
}
