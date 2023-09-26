vpath %.c src/mandatory src/mandatory/environment src/mandatory/parse
vpath %.c src/mandatory/tokens src/mandatory/utils src/mandatory/builtin
vpath %.c src/bonus

NAME := minishell
CFLAGS := -Wextra -Wall -Werror
CFLAGS += -g3

CC := cc
RM := rm -rf

LIBTF_DIR := ./lib/libft
LIBS := -L$(LIBTF_DIR) -lft -lreadline

OBJ_DIR := build
INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR) -I$(LIBTF_DIR)

SRCS := minishell.c
SRCS += create_envs.c find_env.c update_env.c add_env.c uptade_pwd_env.c delete_env.c
SRCS += syntax_tree.c parser.c analysis.c
SRCS += tokenizer.c sanitize_tokens.c create_token_array.c get_redirects.c new_token.c
SRCS += env.c pwd.c cd.c exit.c unset.c export.c
SRCS += delete.c count_args.c is_builtin.c init_minishell.c is_redirect.c
SRCS += is_exe.c is_token.c is_operator.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS_BONUS := minishell_bonus.c
OBJS_BONUS := $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: libft $(NAME)

init_modules: $(LIBTF_DIR)
	git submodule update --init

update_modules: init_modules
	git submodule foreach git pull origin master --rebase

libft:
	@$(MAKE) -j50 -C $(LIBTF_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBTF_DIR):
	mkdir -p $(LIBTF_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)

bonus: libft $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./readline.supp -q ./$(NAME)

clean: 
	@$(MAKE) -C $(LIBTF_DIR) clean
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@$(MAKE) -C $(LIBTF_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus libft update_modules init_modules val
