/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:40:32 by pitran            #+#    #+#             */
/*   Updated: 2025/03/13 17:59:22 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	create_paren_struct(t_token *token)
{
	t_parenthesis	*new_parenthesis;
	
	new_parenthesis = malloc(sizeof(t_parenthesis));
	if (!new_parenthesis)
		return (NULL);
	new_parenthesis->token = token;
	new_parenthesis->next = NULL;
	new_parenthesis->found = false;
}

void	link_paren_struct(t_parenthesis *new_parenthesis, t_parenthesis **parenthesis_list)
{
	t_parenthesis *current;

	if (!new_parenthesis || !parenthesis_list)
		return;
	if (!*parenthesis_list)
	{
		*parenthesis_list = new_parenthesis;
		return ;
	}
	current = *parenthesis_list;
	while (current->next)
		current = current->next;
	current->next = new_parenthesis;
}

t_parenthesis	**assign_paren_struct(t_token **token_list)
{
	t_parenthesis	**parenthesis_list;
	t_token			*current;

	parenthesis_list = malloc(sizeof(t_token *));
	if (!parenthesis_list)
		return (NULL);
	*parenthesis_list = NULL;
	current = *token_list;
	while (current)
	{
		if (current->type == PAREN_OPEN || current->type == PAREN_CLOSE)
		{
			create_paren_struct(current);
			link_paren_struct(current, parenthesis_list);
		}
		current = current->next;
	}
	return (parenthesis_list)
}

void	find_parenthesis_list(t_parenthesis **parenthesis_list)
{
	t_parenthesis	*current;
	t_parenthesis	*current_pair;

	while (current)
	{
		if (current->token->type == PAREN_OPEN && current->found == false)
		{
			current->found = true;
			current_pair = current;
			while (current_pair->token->type != PAREN_CLOSE && current_pair->found != true)
				current_pair = current_pair->next;
			current_pair->found = true;
		}		
		current = current->next;
	}
}
