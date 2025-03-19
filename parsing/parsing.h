/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:20:14 by pitran            #+#    #+#             */
/*   Updated: 2025/03/19 17:15:37 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* Token typology */
typedef enum
{
	DEFAULT = 0,    /* Initial state */
	WORD = 1,       /* Commands and arguments */
	ASSIGNMENT = 2, /* Variable assignments */
	
	QUOTE = 3,        /* Generic quote */
	SINGLE_QUOTE = 4, /* 'string' */
	DOUBLE_QUOTE = 5, /* "string" */
	
	REDIR = 6,        /* Generic redirection */
	REDIR_IN = 7,     /* < */
	REDIR_OUT = 8,    /* > */
	REDIR_APPEND = 9, /* >> */
	HEREDOC = 10,     /* << */
	
	OPERATOR = 11,  /* Generic operator */
	PIPE = 12,      /* | */
	AND = 13,       /* && */
	OR = 14,        /* || */
	
	PARENTHESIS = 15,  /* Generic parenthesis */
	PAREN_OPEN = 16,   /* ( */
	PAREN_CLOSE = 17,  /* ) */
	
	SPECIAL_CARACTER = 18, /* Special characters */
	ENV_VAR = 19,         /* $VAR */
	EXIT_STATUS = 20,     /* $? */
	ESCAPE = 21,          /* \ (backslash) */
	COMMENT = 22,         /* # */
	T_NEWLINE = 23,       /* End of command */
	T_EOF = 24,           /* End of input */
	
	UNKNOWN = 25     /* Error handling */
}	t_token_type;

/* Token structure */
typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* I-TOKENIZATION */

/* Retrieve */
t_token          **tokenize_input(char *command);
t_token          **extract_token(char **command, t_token_type type, 
				t_token **token_list);
t_token          *handle_token_type(char **command, t_token_type type, 
				t_token *new_token);

/* Tokenize */
t_token          *tokenize_word(char **command, t_token *token);
t_token          *tokenize_quote(char **command, t_token *token);
t_token          *tokenize_redir(char **command, t_token *token);
t_token          *tokenize_operator(char **command, t_token *token);
t_token          *tokenize_parenthesis(char **command, t_token *token);
t_token          *tokenize_special_caracter(char **command, t_token *token);
void             define_special_caracter(char **command, t_token *token);
void             define_double_redirection(char **command, t_token *token, 
				int *len);
void             define_bonus_operator(char **command, t_token *token, int *len);

/* Tokens */
t_token			*create_token(void);
void			link_token(t_token *token, t_token **token_list);
void			free_token(t_token *token);
void			free_token_list(t_token **token_list);

/* Characters */
int              is_space(char c);
int              is_quote(char c);
int              is_redirection(char c);
int              is_operator(char c);
int              is_command_char(char c);
int              is_parenthesis(char c);
int              is_special_caracter(char c);

/* Helpers */
int              find_word_len(char *content);

/* II-SYNTAX CHECK */

/* 1) PARENTHESIS */
/* Parenthesis check */
int              paren_syntax_is_valid(t_token **token_list);
int				count_tokens(t_token **token_list);
int				check_token(t_token *cur, t_token **stack, int *top);
int				quote_syntax_is_valid(t_token **token_list);
int				redir_syntax_is_valid(t_token **token_list);
int				pipe_syntax_is_valid(t_token **token_list);

#endif