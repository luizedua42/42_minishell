/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/03 16:48:10 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

typedef enum e_token_type
{
	OR = 0,
	PIPE = 1,
	AND = 2,
	REDIRECT_IN = 3,
	REDIRECT_OUT = 4,
	HEREDOC_IN = 5,
	HEREDOC_OUT = 6,
	OPEN_PARENTHESIS = 7,
	CLOSE_PARENTHESIS = 8,
	WORD = 9,
	END_ARRAY = 10,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
}						t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
}						t_env;

typedef struct s_node
{
	t_token_type		type;
	char				*value;
}						t_node;

typedef struct s_fd
{
	char				*redirect_to;
	t_token_type		type;
}						t_fd;

typedef struct s_fds
{
	t_fd				fd_in;
	t_fd				fd_out;
	t_fd				fd_error;
}						t_fds;

typedef struct s_minishell
{
	t_list				*tokens;
	t_list				*envs;
	t_fds				fds;
	unsigned char		exit_status;
	struct t_minishell	**next;
}						t_minishell;

void					init_minishell(t_minishell *minishell, char **envp);

// Parse
bool					syntax_analysis(t_token_type *token_array);
bool					token_analysis(t_token_type *token_array,
							t_token_type type);
bool					redirection_analysis(t_token_type *token_array);
bool					check_parenthesis(t_token_type *token_array);

// Builtins
int						pwd(void);
int						env(t_minishell *minishell);
int						cd(t_minishell *minishell, char **args);
int						minishell_exit(t_minishell *minishell);
int						unset(t_minishell *minishell, char **args);
int						minishell_export(t_minishell *minishell, char **args);
int						builtin_selector(t_minishell *minishell, char **args);
int						echo(char **args);

// Utils
size_t					count_args(char **args);
void					clear_fds(t_minishell *minishell);
void					del_fd(t_fd *fd);
void					del_env(void *content);
void					del_token(void *content);
bool					is_redirect(t_token_type type);
bool					is_token(char c);
bool					is_exe(t_token_type type);
bool					is_operator(t_token_type type);
bool					is_space(char c);
char					*create_prompt(void);

// Tokens
void					sanitize_tokens(t_minishell *minishell);
void					get_redirects(t_minishell *minishell);
bool					create_tokens(t_list **tokens, char *cmd);
bool					new_token(t_list **tokens, t_token_type type,
							char *value, size_t *index);
t_token_type			*create_token_array(t_list *tokens, size_t *i);

// Enviroments
t_list					*create_envs(char **envp);
t_env					*find_env(t_list *envs, char *key);
char					*find_env_value(t_list *envs, char *key);
t_list					*find_env_element(t_list *envs, char *key);
void					uptade_pwd_env(t_list *envs);
t_env					*update_env(t_list *envs, char *key, char *value);
t_env					*add_env(t_list *envs, char *key, char *value);
bool					delete_env(t_minishell *minishell, char *key);

// Wildcard
char					*expand(t_minishell *minishell, char *str,
							bool is_in_quotes);
bool					wild_match(const char *pattern, const char *string);
char					*wild_get(char *wildcard);
void					parse_env(t_minishell *minishell, t_list **words,
							char *str, size_t *index);
char					*join_words(t_list *words);
void					parse_quote(t_minishell *minishell, t_list **words,
							char *str, size_t *index);

#endif
