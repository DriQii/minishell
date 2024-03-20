CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = minishell

SRCS = exec.c \

OBJS = $(SRCS:.c=.o)

SRCSDIR = srcs/

OBJSDIR = objs/

all     :   $(NAME)

$(OBJSDIR)$(OBJS) : $(SRCSDIR)$(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) :   $(OBJSDIR)$(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJSDIR)$(OBJS) -o $(NAME) -L./libft/ -lft -I$(brew --prefix readline)/include -L$(brew --prefix readline)/lib -lreadline
clean   :
	$(MAKE) -C libft clean
	rm -rf $(OBJ)
fclean  :   clean
	rm -f libft/libft.a
	rm -f $(NAME)
	
re      :   fclean all