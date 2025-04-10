/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:22:05 by pitran            #+#    #+#             */
/*   Updated: 2025/03/26 16:03:22 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int parse_input(char *command)
{
	t_token **token_list;
	int      syntax_valid;

	if (!command)
		return (1);
	token_list = tokenize_input(command);
	if (!token_list)
		return (1);
	syntax_valid = syntax_is_valid(token_list);
	if (syntax_valid)
		print_token_list(token_list);
	else
		return(free_token_list(token_list), printf("Syntax error in command\n"));
	free_token_list(token_list);
	return (0);
}

void print_token_list(t_token **token_list)
{
    t_token *current;
    int     token_count;

    token_count = 0;
    if (!token_list || !*token_list)
    {
        printf("No tokens to display\n");
        return;
    }
    current = *token_list;
    while (current)
    {
        printf("Token %d --> Type: %d, Content: '%s'\n", 
               token_count++, current->type, current->content);
        current = current->next;
    }
}