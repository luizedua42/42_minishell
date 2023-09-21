/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/21 20:51:14 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <stdbool.h>

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

typedef struct s_env
{
	char			*key;
	char			*value;
}					t_env;

typedef struct s_node
{
	t_token_type	type;
	char			    *value;
}					t_node;

t_list				*create_envs(char **envp);
t_list		*create_tokens(char *command);
int			*create_token_array(t_list *tokens, int *i);
void		print_token_array(int *token_array, int size);
bool		syntax_analysis(int *token_array);
bool	new_token(t_list **tokens, t_token_type type, char *value,
	size_t *index);

#endif
