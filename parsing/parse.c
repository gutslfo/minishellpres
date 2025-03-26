/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:22:05 by pitran            #+#    #+#             */
/*   Updated: 2025/03/26 15:42:45 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    parse_input()
{
	char 	*command;
	t_token	**token_list;

	command = read_command();
	token_list = tokenize_input(command);
	print_token_list(token_list);
	
}

void	print_token_list(t_token **token_list)
{
	t_token *current = *token_list;

	int token_count = 0;
	while (current)
	{
		printf("Token %d --> Type : %d, Content: '%s\n", token_count++, current->type, current->content);
		current = current->next;
	}
}