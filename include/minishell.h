/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/21 03:44:10 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>

// Defines
# define COMMAND_NOT_FOUND 127
# define PATH_ERROR 126
# define PATH_STR "PATH="

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
	SHELL = 10,
	END_ARRAY = 11,
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

typedef struct s_fd
{
	char			*redirect_to;
	t_token_type	type;
	int				fd;
}					t_fd;

typedef struct s_minishell
{
	t_list			*tokens;
	t_list			*envs;
	t_list			*shells;
	int				*pids;
	unsigned char	exit_status;
}					t_minishell;

typedef struct s_bfd
{
	int				last_fdin;
	int				last_fdout;
	int				safe_in;
	int				safe_out;
}					t_bfd;

// Parse
bool				syntax_analysis(t_token_type *token_array);
bool				token_analysis(t_token_type *token_array,
						t_token_type type);
bool				redirection_analysis(t_token_type *token_array);
bool				check_parenthesis(t_token_type *token_array);
t_minishell			*create_sub_shells(t_list **tokens, t_list *envs, \
										int exit_status);
void				clear_shell(void *minishell);
void				clear_subshells(void *minishell);

// Builtins
int					pwd(void);
int					env(t_minishell *minishell);
int					cd(t_minishell *minishell, char **args);
int					minishell_exit(t_minishell *minishell, char **args,
						bool has_pipe);
int					unset(t_minishell *minishell, char **args);
int					minishell_export(t_minishell *minishell, char **args);
int					builtin_selector(t_minishell *minishell, char **args,
						bool has_pipe);
int					echo(char **args);
t_bfd				builtin_fds(t_list *child_files);

// Utils
size_t				count_args(char **args);
void				del_fd(void *content);
void				del_env(void *content);
void				del_token(void *content);
void				free_token_array(t_list **token_array);
bool				is_redirect(t_token_type type);
bool				is_token(char c);
bool				is_exe(t_token_type type);
bool				is_operator(t_token_type type);
bool				is_space(char c);
char				*create_prompt(void);
bool				is_builtin(char *cmd);
void				my_dup(int fd, int fd2);
void				handle_signal(void);
void				handle_signal_child(void);
t_minishell			*init_minishell(char **envp);

// Tokens
void				sanitize_tokens(t_list **original_tokens);
t_list				*get_redirects(t_list *tokens);
bool				create_tokens(t_list **tokens, char *cmd);
bool				new_token(t_list **tokens, t_token_type type, char *value,
						size_t *index);
void				sanitize_emptyvar(t_list **original_tokens);
t_token_type		*create_token_array(t_list *tokens);

// Enviroments
t_list				*create_envs(char **envp);
t_env				*find_env(t_list *envs, char *key);
char				*find_env_value(t_list *envs, char *key);
t_list				*find_env_element(t_list *envs, char *key);
void				uptade_pwd_env(t_list *envs);
t_env				*update_env(t_list *envs, char *key, char *value);
t_env				*add_env(t_list *envs, char *key, char *value);
bool				delete_env(t_minishell *minishell, char *key);
t_env				*export_env(t_minishell *minishell, char *key, char *value);

// Wildcard
char				*expand(t_minishell *minishell, char *str,
						bool is_in_quotes);
bool				wild_match(const char *pattern, const char *string);
char				*wild_get(char *wildcard);
void				parse_env(t_minishell *minishell, t_list **words, char *str,
						size_t *index);
char				*join_words(t_list *words);
void				parse_quote(t_minishell *minishell, t_list **words,
						char *str, size_t *index);
void				expand_all(t_minishell *minishell, t_list *tokens);

// Executor
bool				open_file(t_minishell *minishell, t_fd *file);
void				here_doc(t_minishell *minishell, t_fd *fd);
char				*get_path(char *cmd, char **env);
t_list				**split_pipes(t_list *tokens);
void				*select_token_value(void *token);
void				*select_env(void *content);
size_t				lst_matrix_len(t_list **matrix);
int					executor(t_minishell *minishell);
int					exec(char **cmds, t_minishell *minishell);
int					do_pipe(t_minishell *minishell, t_list *tokens, size_t i,
						t_list **token_array);
void				close_fds(t_list *fds);
bool				open_redirects(t_minishell *minishell, t_list *fds,
						t_list **token_array, bool has_pipe);
int					get_last_fd(int type, t_list *fds, int default_fd);
int					builtin_exit(char **cmds, t_list **token_array, int ret, \
									t_minishell *minishell);

// Validation
int					pipe_validation(bool is_last, int *pipedes,
						int hostage_pipe);
int					fork_validation(int *pid);

// Prints
void				print_tokens(t_minishell *minishell, t_list *tokens);
void				print_envs(t_list *envs);
void				print_sub_shells(t_minishell *minishell, int level);

#endif
