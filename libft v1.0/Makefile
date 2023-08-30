NAME := libft.a
OBJ = $(FTS:%.c=%.o)
BOBJ = $(BFTS:%.c=%.o)

BFTS:=  ft_lstadd_back_bonus.c ft_lstdelone_bonus.c  ft_lstadd_front_bonus.c ft_lstiter_bonus.c ft_lstnew_bonus.c ft_lstclear_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstmap_bonus.c


FTS := ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memset.c ft_strdup.c ft_strlen.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_memcpy.c ft_memcmp.c ft_memchr.c ft_strchr.c ft_memmove.c ft_strrchr.c ft_calloc.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_itoa.c ft_striteri.c ft_strmapi.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_split.c


%.o : %.c
	cc -c -Wall -Wextra -Werror $< -I . -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $^

clean :
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(BOBJ)

$(BOBJ): 
	cc -Wall -Wextra -Werror -c $(@:.o=.c) -o $@
	ar -rcs $(NAME) $@
	
