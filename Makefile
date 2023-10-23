vpath %.c src/mandatory src/mandatory/environment src/mandatory/parse
vpath %.c src/mandatory/tokens src/mandatory/utils src/mandatory/builtin
vpath %.c src/mandatory/expantions
vpath %.c src/mandatory/executor
vpath %.c src/bonus

NAME := minishell
CFLAGS := -Wextra -Wall -Werror
CFLAGS += -g3
JOBS := -j50
MAKEFLAGS += --no-print-directory
YELLOW := $(shell tput setaf 3)
GREEN := $(shell tput setaf 2)
RESET := $(shell tput sgr0)

CC := cc
RM := rm -rf

LIBTF_DIR := ./lib/libft
LIBS := -L$(LIBTF_DIR) -lft -lreadline

OBJ_DIR := build
INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR) -I$(LIBTF_DIR)

SRCS := minishell.c
SRCS += create_envs.c find_env.c update_env.c add_env.c uptade_pwd_env.c 
SRCS += delete_env.c new_token.c
SRCS += parser.c analysis.c clear_shells.c
SRCS += tokenizer.c sanitize_tokens.c create_token_array.c get_redirects.c 
SRCS += env.c pwd.c cd.c exit.c unset.c export.c echo.c builtin_selector.c
SRCS += delete.c count_args.c init_minishell.c is_redirect.c
SRCS += is_exe.c is_token.c is_space.c is_builtin.c my_dup.c
SRCS += executor.c get_path.c here_doc.c open_file.c selects.c split_pipes.c 
SRCS += exec.c do_pipe.c heredoc_sigs.c unlinks.c getters.c
SRCS += expantion.c join_words.c parse_env.c
SRCS += parse_quote.c prompt.c fd_utils.c open_heredoc.c
SRCS += exec_validation.c signals.c builtin_exec.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS_BONUS := minishell_bonus.c
OBJS_BONUS := $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: libft $(NAME)

init_modules: $(LIBTF_DIR)
	git submodule update --init

update_modules: init_modules
	git submodule foreach git pull origin master --rebase

print_start:
	@echo "$(YELLOW)Compiling minishell...$(RESET)"

libft:
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) $(JOBS) -C $(LIBTF_DIR)
	@echo "$(GREEN)libft compiled!$(RESET)"

$(OBJ_DIR)/%.o: %.c include/minishell.h | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBTF_DIR):
	@mkdir -p $(LIBTF_DIR)

$(NAME): print_start $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)minishell compiled!$(RESET)"

bonus: libft $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' --suppressions=./readline.supp -q ./$(NAME)

clean: 
	@$(MAKE) -C $(LIBTF_DIR) clean
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@$(MAKE) -C $(LIBTF_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus libft update_modules init_modules val
