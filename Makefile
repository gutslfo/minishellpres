# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pitran <pitran@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 11:50:43 by pitran            #+#    #+#              #
#    Updated: 2025/05/20 14:44:03 by pitran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline -lncurses

# Source directories
PARSING_DIR = parsing
SYNTAX_DIR = $(PARSING_DIR)/syntax_check
AST_DIR = $(PARSING_DIR)/ast

# Source files
SRC_MAIN = readline/readline.c

SRC_PARSING = $(PARSING_DIR)/retrieve.c \
			  $(PARSING_DIR)/helpers.c \
			  $(PARSING_DIR)/caracter_type.c \
			  $(PARSING_DIR)/caracter_type2.c \
			  $(PARSING_DIR)/tokenize.c \
			  $(PARSING_DIR)/tokenize2.c \
			  $(PARSING_DIR)/tokens.c \
			  $(PARSING_DIR)/parse.c

SRC_SYNTAX = $(SYNTAX_DIR)/syntax_check.c \
			 $(SYNTAX_DIR)/other_type_check.c \
			 $(SYNTAX_DIR)/parenthesis_check.c

SRC_AST = $(AST_DIR)/ast_builder.c \
		  $(AST_DIR)/parsing.c \
		  $(AST_DIR)/nodes.c \
		  $(AST_DIR)/simple_command.c \
		  $(AST_DIR)/utils.c

# Combine all sources
SRCS = $(SRC_MAIN) $(SRC_PARSING) $(SRC_SYNTAX) $(SRC_AST)

# Object files
OBJS = $(SRCS:.c=.o)

# Include directories
INCLUDES = -I.

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Debugging tools
valgrind: $(NAME)
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./$(NAME)

.PHONY: all clean fclean re valgrind