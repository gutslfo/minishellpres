#ifndef PARSING_H
#define PARSING_H

//Retrieve
void    handle_input(char *command);

//Handlers

//Bulk caracter
int     count_words(char *str, char delimiter);

//Tokens
t_token    *create_token(t_token *token);

//Helpers
int     ft_strlen(char *str);


#endif