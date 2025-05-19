/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:30:21 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 16:47:02 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast_node	*create_ast(t_token **token_list)
{
	if (!token_list || !*token_list)
		return (NULL);
	return (parse_command_line(token_list, 0, count_tokens(token_list) - 1));
}

t_token	*get_token_at_index(t_token **token_list, int index)
{
	t_token	*current;
	int		i;

	if (!token_list || !*token_list || index < 0)
		return (NULL);
	
	current = *token_list;
	i = 0;
	
	while (current && i < index)
	{
		current = current->next;
		i++;
	}
	
	return (current);
}

int	is_in_subshell(t_token **token_list, int index)
{
	int		i;
	int		paren_level;
	t_token	*current;

	paren_level = 0;
	i = 0;
	while (i < index)
	{
		current = get_token_at_index(token_list, i);
		if (current->type == PAREN_OPEN)
			paren_level++;
		else if (current->type == PAREN_CLOSE)
			paren_level--;
		i++;
	}
	return (paren_level > 0);
}

int	matching_parentheses(t_token **tokens, int start, int end)
{
	t_token	*start_token;
	t_token	*end_token; 
	t_token	*current;
	int		level;
	int		i;

	start_token = get_token_at_index(tokens, start);
	end_token = get_token_at_index(tokens, end);
	
	if (!start_token || !end_token)
		return (0);
		
	if (start_token->type != PAREN_OPEN || end_token->type != PAREN_CLOSE)
		return (0);
	
	level = 0;
	i = start;
	while (i <= end)
	{
		current = get_token_at_index(tokens, i);
		if (!current)
			return (0);
			
		if (current->type == PAREN_OPEN)
			level++;
		else if (current->type == PAREN_CLOSE)
		{
			level--;
			if (level == 0 && i != end)
				return (0);
		}
		i++;
	}
	return (level == 0);
}

int	find_matching_parenthesis(t_token **tokens, int open_pos, int end)
{
	int	level;
	int	i;

	if (tokens[open_pos]->type != PAREN_OPEN)
		return (-1);
	level = 1;
	i = open_pos + 1;
	while (i <= end)
	{
		if (tokens[i]->type == PAREN_OPEN)
			level++;
		else if (tokens[i]->type == PAREN_CLOSE)
		{
			level--;
			if (level == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}