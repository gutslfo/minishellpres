NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -lncurses

UNAME_S := $(shell uname -s)

SRCS := $(shell find . -name "*.c" ! -path "./tests/*")

OBJS = $(SRCS:.c=.o)

all: $(NAME)

libminishell.a : $(OBJS)
	ar rcs $@ $(OBJS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(LFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) $(CFLAGS) $(LFLAGS) $(INCLUDES) -c $< -o $@

valgrind:
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./$(NAME)

