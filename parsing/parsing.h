#ifndef PARSING_H
#define PARSING_H

//Token typology
typedef enum {

	//Initial state
	DEFAULT, 
	
	//Basic elements 
	WORD,			// Commands and arguments
	ASSIGNMENT,		// Variable assignments 

	//Quotes
	QUOTE,
	SINGLE_QUOTE,	// 'string'
	DOUBLE_QUOTE,	// "string"

	//Redirections
	REDIR,
	REDIR_IN, 		// <
	REDIR_OUT,		// >
	REDIR_APPEND,	// >>
	HEREDOC,		// <<

	//Operators
	OPERATOR,
	PIPE,			// |
	AND,			// &&
	OR,				// ||
	SEMICOLON,		// ;

	//Grouping
	PARENTHESIS, 
	PAREN_OPEN,		// (
	PAREN_CLOSE,	// )

	//Special caracters
	SPECIAL_CARACTER,
	ENV_VAR,		// $VAR
	EXIT_STATUS,	// $?
	ESCAPE,			// \ (backslash)
	COMMENT,		// #
	T_NEWLINE,		// End of command
	T_EOF,			// End of input

	//Error handling
	UNKNOWN 
}	token_type;

//Token structure
typedef struct s_token{
	token_type	        type;
	char		        *content;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

//Retrieve
t_token		**tokenize_input(char *command);
char		*extract_token(char *command, token_type type, t_token **token_list);
char		*handle_token_type(char *command, token_type type, t_token *new_token);

//Tokenize
char	    *tokenize_word(char *command, t_token *token);
char	    *tokenize_quote(char *command, t_token *token);
char	    *tokenize_redir(char *command, t_token *token);
char	    *tokenize_operator(char *command, t_token *token);
char	    *tokenize_parenthesis(char *command, t_token *token);
char	    *tokenize_special_caracter(char *command, t_token *token);
void	    define_special_caracter(char *command, t_token *token);
void	    define_double_redirection(char *command, t_token *token, int *len);
void	    define_bonus_operator(char *command, t_token *token, int *len);

//Tokens
t_token	    *create_token(t_token *new_token);
t_token	    **link_token(t_token *token, t_token **token_list);

//Caracters
int         is_space(char c);
int	        is_quote(char c);
int	        is_redirection(char c);
int	        is_operator(char c);
int	        is_command_char(char c);
int	        is_parenthesis(char c);
int	        is_special_caracter(char c);

//Helpers
int            find_word_len(char *content);

#endif
