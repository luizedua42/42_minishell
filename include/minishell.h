/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/09/24 02:43:55 by pdavi-al         ###   ########.fr       */
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

typedef struct s_fds
{
	int				fd_in;
	int				fd_out;
	int				fd_error;
}					t_fds;

typedef struct s_minishell
{
	t_list			*tokens;
	t_list			*envs;
	t_fds			fds;
	unsigned char	exit_status;
}					t_minishell;

t_list				*create_tokens(char *command);
t_token_type		*create_token_array(t_list *tokens, int *i);
void				print_token_array(int *token_array, int size);
bool				syntax_analysis(t_token_type *token_array);
bool				new_token(t_list **tokens, t_token_type type, char *value,
						size_t *index);
void				init_minishell(t_minishell *minishell, char **envp);

// Builtins
int					pwd(void);
int					env(t_list *envs);
int					cd(char **args, t_list *envs);
int					minishell_exit(t_minishell *minishell);
int					unset(t_minishell *minishell, char **args);
void				del_env(void *content);
void				del_token(void *content);
size_t				count_args(char **args);
bool				is_builtin(t_list **tokens, char *command, size_t *i);

// Enviroments
t_list				*create_envs(char **envp);
t_env				*find_env(t_list *envs, char *key);
char				*find_env_value(t_list *envs, char *key);
t_list				*find_env_element(t_list *envs, char *key);
void				uptade_pwd_env(t_list *envs);
t_env				*update_env(t_list *envs, char *key, char *value);
t_env				*add_env(t_list *envs, char *key, char *value);

#endif
