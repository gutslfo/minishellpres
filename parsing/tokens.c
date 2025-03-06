/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:59:05 by pitran            #+#    #+#             */
/*   Updated: 2025/03/06 14:58:05 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Token allocation and initialisation
t_token	*create_token(t_token *new_token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

char	*tokenize_word(char *command, t_token *token)
{
	int		len;
	int		i;

	token->type = WORD;
	len = find_token_len(command, WORD);
	token->content = (char *)malloc(sizeof(char) * len + 1);
	i = 0;
	while (is_command_char(command[i]))
	{
		token->content[i] = command[i];
		i++;
	}
	token->content[i] = '\0';
	return (command[i]);
}


t_token	**link_token(t_token *token, t_token **token_list)
{
	t_token	*current;

	current = *token_list;
	while (current && current->next)
		current = current->next;
	current->next = token;
	token->prev = current;
	return (token_list);
}
