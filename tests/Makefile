NAME = test_minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -lncurses

SRCS = split.c main.c
OBJS = $(SRCS:.c=.o)

MINISHELL_DIR = ../
INCLUDES = -I$(MINISHELL_DIR)

all: $(NAME)

$(NAME): $(OBJS) libminishell.a
	$(CC) $(OBJS) -L$(MINISHELL_DIR) -lminishell $(LFLAGS) -o $(NAME)

libminishell.a:
	make -C $(MINISHELL_DIR) libminishell.a

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MINISHELL_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MINISHELL_DIR) fclean

re: fclean all