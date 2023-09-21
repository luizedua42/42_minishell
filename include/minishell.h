/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/20 20:21:32 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	OR,
	PIPE,
	AND,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC_IN,
	HEREDOC_OUT,
	QUOTE,
	DQUOTE,
	DOLLAR_SIGN,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	WORD,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}					t_token;

typedef struct s_node
{
	t_token_type	type;
	char			*value;
}					t_node;

t_list	*create_tokens(char *command);
t_tree	*create_tree(t_list *tokens);

#endif
