/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:40:29 by pitran            #+#    #+#             */
/*   Updated: 2025/05/09 15:10:27 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_lowest_precedence_op(t_token **tokens, int start, int end)
{
	int	result;
	int	lowest_precedence;
	int	current_precedence;
	int	paren_level;
	int	i;

	result = -1;
	lowest_precedence = INT_MAX;
	paren_level = 0;
	i = start;
	while (i <= end)
	{
		if (tokens[i]->type == PAREN_OPEN)
			paren_level++;
		else if (tokens[i]->type == PAREN_CLOSE)
			paren_level--;
		if (paren_level == 0 && (tokens[i]->type == PIPE || tokens[i]->type == AND
				|| tokens[i]->type == OR || tokens[i]->type == SEMICOLON))
		{
			current_precedence = get_operator_precedence(tokens[i]->type);
			if (current_precedence <= lowest_precedence)
			{
				lowest_precedence = current_precedence;
				result = i;
			}
		}
		i++;
	}
	return (result);
}