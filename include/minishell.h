/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/21 21:55:32 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

typedef enum e_token_type
{
	END_ARRAY = -1,
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
	BUILTIN,
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
	char			*value;
}					t_node;

t_list				*create_envs(char **envp);
t_list				*create_tokens(char *command);
t_token_type		*create_token_array(t_list *tokens, int *i);
void				print_token_array(int *token_array, int size);
bool				syntax_analysis(int *token_array);
bool				new_token(t_list **tokens, t_token_type type, char *value,
						size_t *index);

// Builtins
void				pwd(void);
void				env(t_list *envs);
void				cd(char **args);
size_t				count_args(char **args);
bool				is_builtin(t_list **tokens, char *command, size_t *i);

#endif
