/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:20:14 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 15:21:07 by pitran           ###   ########.fr       */
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
	SEMICOLON = 15, /* ; */
	
	PARENTHESIS = 16,  /* Generic parenthesis */
	PAREN_OPEN = 17,   /* ( */
	PAREN_CLOSE = 18,  /* ) */
	
	SPECIAL_CARACTER = 19, /* Special characters */
	ENV_VAR = 20,         /* $VAR */
	EXIT_STATUS = 21,     /* $? */
	ESCAPE = 22,          /* \ (backslash) */
	COMMENT = 23,         /* # */
	T_NEWLINE = 24,       /* End of command */
	T_EOF = 25,           /* End of input */
	
	UNKNOWN = 26     /* Error handling */
}	t_token_type;

/* Token structure */
typedef struct s_token
{
	t_token_type	type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/* AST Node Typology */
typedef enum
{
	AST_COMMAND = 1,    /* Simple command with args and redirections */
	AST_PIPE = 2,       /* Pipe operator | */
	AST_AND = 3,        /* AND operator && */
	AST_OR = 4,         /* OR operator || */
	AST_SUBSHELL = 5    /* Commands in parentheses () */
}	t_ast_type;

/* Redirection type */
typedef enum
{
	REDIR_TYPE_IN = 1,       /* < */
	REDIR_TYPE_OUT = 2,      /* > */
	REDIR_TYPE_APPEND = 3,   /* >> */
	REDIR_TYPE_HEREDOC = 4   /* << */
}	t_redir_type;

/* Redirection structure */
typedef struct s_redirection
{
	t_redir_type			type;
	char					*file;
	struct s_redirection	*next;
}	t_redirection;

/* Command data structure */
typedef struct s_cmd_data
{
	char			**args;
	t_redirection	*redirections;
}	t_cmd_data;

/* Binary operator data structure */
typedef struct s_binary_data
{
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_binary_data;

/* Subshell data structure */
typedef struct s_subshell_data
{
	struct s_ast_node	*child;
}	t_subshell_data;

/* AST Node Structure */
typedef struct s_ast_node
{
	t_ast_type	type;
	union
	{
		t_cmd_data		command;
		t_binary_data	binary;
		t_subshell_data	subshell;
	}	data;
}	t_ast_node;

/* I-TOKENIZATION */

/* Retrieve */
t_token		**tokenize_input(char *command);
t_token		**extract_token(char **command, t_token_type type, 
				t_token **token_list);
t_token		*handle_token_type(char **command, t_token_type type, 
				t_token *new_token);

/* Tokenize */
t_token		*tokenize_word(char **command, t_token *token);
t_token		*tokenize_quote(char **command, t_token *token);
t_token		*tokenize_redir(char **command, t_token *token);
t_token		*tokenize_operator(char **command, t_token *token);
t_token		*tokenize_parenthesis(char **command, t_token *token);
t_token		*tokenize_special_caracter(char **command, t_token *token);
void		define_special_caracter(char **command, t_token *token);
void		define_double_redirection(char **command, t_token *token, int *len);
void		define_bonus_operator(char **command, t_token *token, int *len);

/* Tokens */
t_token		*create_token(void);
void		link_token(t_token *token, t_token **token_list);
void		free_token(t_token *token);
void		free_token_list(t_token **token_list);

/* Characters */
int			is_space(char c);
int			is_quote(char c);
int			is_redirection(char c);
int			is_operator(char c);
int			is_command_char(char c);
int			is_parenthesis(char c);
int			is_special_caracter(char c);

/* Helpers */
int			find_word_len(char *content);

/* II-SYNTAX CHECK */

/* Specific syntax checks by type */
int			paren_syntax_is_valid(t_token **token_list);
int			count_tokens(t_token **token_list);
int			check_token(t_token *cur, t_token **stack, int *top);
int			quote_syntax_is_valid(t_token **token_list);
int			redir_syntax_is_valid(t_token **token_list);
int			operator_syntax_is_valid(t_token **token_list);
/* Overall syntax check */
int			syntax_is_valid(t_token **token_list);

/* III- AST */
/* Main AST functions */
t_ast_node	*create_ast(t_token **token_list);
t_ast_node	*parse_command_line(t_token **tokens, int start, int end);
t_ast_node	*parse_simple_command(t_token **tokens, int start, int end);

/* Token access functions */
t_token		*get_token_at_index(t_token **token_list, int index);
t_token		**list_to_array(t_token **token_list, int count);

/* Operator and parenthesis utilities */
int			is_in_subshell(t_token **token_list, int index);
int			find_matching_parenthesis(t_token **tokens, int open_pos, int end);
int			find_lowest_precedence_op(t_token **tokens, int start, int end);
int			get_operator_precedence(t_token_type type);
int			matching_parentheses(t_token **tokens, int start, int end);

/* Node creation functions */
t_ast_node	*create_command_node(char **args);
t_ast_node	*create_operator_node(t_ast_type type, t_ast_node *left, 
				t_ast_node *right);
t_ast_node	*create_subshell_node(t_ast_node *child);

/* Redirection functions */
t_redirection	*create_redirection(t_redir_type type, char *file);
void			add_redirection(t_ast_node *cmd_node, t_redirection *redir);
int				is_redirection_token(t_token_type type);
t_redir_type	token_to_redir_type(t_token_type type);
int				count_args(t_token **tokens, int start, int end);
char			**extract_args(t_token **tokens, int start, int end);
void			extract_redirections(t_ast_node *node, t_token **tokens,
					int start, int end);

/* Memory management */
void		free_ast_node(t_ast_node *node);
void		free_string_array(char **array);
void		free_redirections(t_redirection *redirections);

/* Debug utilities */
void		print_ast(t_ast_node *node, int depth);
void		print_redirections(t_redirection *redirections, int depth);

/* IV-PARSE */
/* Main parsing function */
int			parse_input(char *command);
void		print_token_list(t_token **token_list);

#endif