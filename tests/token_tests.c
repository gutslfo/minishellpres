/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:40:34 by pitran            #+#    #+#             */
/*   Updated: 2025/03/12 15:31:57 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    test_tokenize_input()
{
    printf("TOKENIZE INPUT\n\n");
    t_token **test_list;
    
    char    *word_test = "echo";
    
    test_list = tokenize_input(word_test);

    t_token *current;
    
    current = *test_list;

    while (current)
    {
        printf("Token type: %d\n", current->type);
        printf("Token content: %s\n", current->content);
        current = current->next;
    }
}