/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luizedua <luizedua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 19:08:04 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/10/24 21:01:11 by luizedua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>

// Defines
# define COMMAND_NOT_FOUND 127
# define CTRLC_RETURN 130
# define PATH_ERROR 126
# define PATH_STR "PATH="

typedef enum e_token_type
{
	PIPE = 0,
	REDIRECT_IN = 1,
	REDIRECT_OUT = 2,
	HEREDOC_IN = 3,
	HEREDOC_OUT = 4,
	WORD = 5,
	END_ARRAY = 6,
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
	int				*pids;
	int				exit_status;
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
bool				redirection_analysis(t_token_type *token_array);
void				clear_shell(void *minishell);
void				clear_shell_content(void *minishell);

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
bool				is_space(char c);
char				*create_prompt(void);
bool				is_builtin(char *cmd);
void				my_dup(int fd, int fd2);
void				handle_signal(void);
void				handle_signal_child(void);
void				signal_handler_child_heredoc(void);
t_minishell			*init_minishell(char **envp);
void				unlink_all(t_list *tokens);

// Tokens
bool				sanitize_tokens(t_list **original_tokens);
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
void				expand_env(size_t i, char *str, char **word, t_list *envs);

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
bool				expand_all(t_minishell *minishell, t_list *tokens);

// Executor
bool				open_file(t_fd *file);
void				here_doc(t_minishell *minishell, t_token *fds, char *index);
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
int					builtin_exit(char **cmds, t_list **token_array, int ret,
						t_minishell *minishell);
bool				open_here_docs(t_minishell *minishell, t_list *tokens);
void				heredoc_err(char *line, char *limiter, size_t limiter_len);
int					close_pipedes(int *pipedes);
bool				path_validation(char *cmd);
int					close_sysfd(int ret);

// Validation
int					pipe_validation(bool is_last, int *pipedes,
						int hostage_pipe);
int					fork_validation(int *pid);

// Getter
t_minishell			*getset_mini(t_minishell *minishell);
char				*getset_filename(char *file_name);
int					getset_fd(int fd);

#endif
