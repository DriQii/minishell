CC = gcc

CFLAGS = -Wall -Wextra -g

NAME = minishell

SRCS = srcs/main.c\
		srcs/utils.c\
		srcs/parsing.c \
		srcs/parsing_utils.c \
		srcs/parsing_utils2.c \
		srcs/builtins.c \
		srcs/builtins_exec.c \
		srcs/builtins_utils.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

objs/%.o : src/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) :   $(OBJS)
	@echo "Make..."
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft/ -lft -I$(brew --prefix readline)/include -L$(brew --prefix readline)/lib -lreadline
	@mv srcs/*.o objs/
	@echo "Make Completed !"
clean   :
	@echo "Clean..."
	@make -C libft clean
	@rm -rf objs/*.o
	@echo "Clear !"
fclean  :   clean
	@rm -f libft/libft.a
	@rm -f $(NAME)
	
re      :   fclean all