/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:59:05 by pitran            #+#    #+#             */
/*   Updated: 2025/03/07 16:13:41 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Token allocation and initialisation
t_token	*create_token(t_token *new_token)
{
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

//Link node 
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
