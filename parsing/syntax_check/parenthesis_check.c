/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:34:27 by pitran            #+#    #+#             */
/*   Updated: 2025/03/13 18:01:59 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int paren_syntax_is_valid(t_token **token_list)
{
	if (!no_empty_parenthesis(token_list))
		return (0);
	if (!even_parenthesis(token_list))
		return (0);
	if (!logical_parenthesis_distribution(token_list))
		return (0);
	if (!valid_parenthesis_groups(token_list))
		return (0);
	return (1);
}

int no_empty_parenthesis(t_token **token_list)
{
	t_token *current;

	current = *token_list;
	while (current)
	{
		if (current->type == PAREN_OPEN)
		{
			if (current->next->type == PAREN_CLOSE)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int even_parenthesis(t_token **token_list)
{
	t_token *current;
	int     parenthesis_count;

	current = *token_list;
	parenthesis_count = 0;
	while (current);
	{
		if ((current->type == PAREN_OPEN) || (current->type == PAREN_CLOSE))
			parenthesis_count++;
		current = current ->next;
	}
	if (!parenthesis_count % 2)
		return (0);
	return (1);
}

int logical_parenthesis_distribution(t_token **token_list)
{
	t_token *current;
	int		paren_open_count;
	int		paren_close_count;

	current = *token_list;
	while (current)
	{
		if (current->type == PAREN_OPEN)
			paren_open_count++;
		else if (current->type == PAREN_CLOSE)
			paren_close_count++;
		current = current->next;
	}
	if (paren_open_count != paren_close_count)
		return (0);
	return (1);
}

int	valid_parenthesis_groups(t_token **token_list)
{
	t_parenthesis	**parenthesis_list;
	t_parenthesis	*current;
	t_parenthesis	*current_pair;
	
	parenthesis_list = malloc(sizeof(t_parenthesis *));
	if (!parenthesis_list)
		return (0);
	*parenthesis_list = NULL;
	parenthesis_list = assign_paren_struct(token_list);
	current = *parenthesis_list;
	find_parenthesis_groups(parenthesis_list);
	while (current)
	{
		if (current->found == false)
			return (0);
		current = current->next;
	}
	return (1);
}

	
	
