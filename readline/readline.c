/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:00:43 by pitran            #+#    #+#             */
/*   Updated: 2025/03/19 17:13:23 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main()
{
    printf("TOKENIZE INPUT TEST\n\n");
    t_token **test_list;
    
    char *word_test = "(i (skfjsflkjv | >> \'am\' \"a\" parenthesis)";
    
    printf("DEBUG: Calling tokenize_input with '%s'\n", word_test);
    test_list = tokenize_input(word_test);
    
    if (!test_list) {
        printf("DEBUG: tokenize_input returned NULL\n");
        return 1;
    }
    
    printf("DEBUG: tokenize_input returned test_list = %p\n", (void*)test_list);
    
    if (!*test_list) {+  
        printf("DEBUG: *test_list is NULL, no tokens were created\n");
        free(test_list);
        return 1;
    }
    
    printf("DEBUG: About to iterate through token list\n");
    t_token *current = *test_list;
    int token_count = 0;
    
    while (current) {
        printf("Token %d - Type: %d, Content: '%s'\n", 
               token_count++, current->type, current->content);
        current = current->next;
    }
    
    if(paren_syntax_is_valid(test_list))
        printf("Valid paren syntax\n");
    if (quote_syntax_is_valid(test_list))
        printf("Valid quote syntax\n"); 
    if (redir_syntax_is_valid(test_list))
        printf("Redir syntax valid\n");
    if (pipe_syntax_is_valid(test_list))
        printf("Pipe syntax is valid\n");
}

/*
int main(void)
{
	char    *command;

	while (1)
	{
		command = readline("Minishell > ");
		if (command)
			add_history(command);
		else
			break;
		//execute_command(command);
	}
}


MAIN

int main()
{
	parse_input(command)
	execute
}*/