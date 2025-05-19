/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:15:46 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 16:46:31 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_operator_precedence(t_token_type type)
{
	if (type == AND || type == OR)
		return (1);
	else if (type == PIPE)
		return (2);
	return (3);
}

int	find_lowest_precedence_op(t_token **tokens, int start, int end)
{
	int		result;
	int		lowest_precedence;
	int		current_precedence;
	int		paren_level;
	int		i;
	t_token	*current;

	result = -1;
	lowest_precedence = INT_MAX;
	paren_level = 0;
	i = start;
	while (i <= end)
	{
		current = get_token_at_index(tokens, i);
		if (!current)
			break;
		if (current->type == PAREN_OPEN)
			paren_level++;
		else if (current->type == PAREN_CLOSE)
			paren_level--;
		if (paren_level == 0 && (current->type == PIPE
				|| current->type == AND || current->type == OR))
		{
			current_precedence = get_operator_precedence(current->type);
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

t_ast_node	*parse_command_line(t_token **tokens, int start, int end)
{
	int			op_pos;
	t_ast_type	node_type;
	t_ast_node	*node;
	int			closing;
	t_token		*start_token;
	t_token		*op_token;

	if (start > end)
		return (NULL);
	
	if (start < 0 || end < 0)
		return (NULL);
	
	// Vérifier matching parens
	start_token = get_token_at_index(tokens, start);
	if (start_token && start_token->type == PAREN_OPEN)
	{
		t_token *end_token = get_token_at_index(tokens, end);
		if (end_token && end_token->type == PAREN_CLOSE)
		{
			// Vérifier que les parenthèses correspondent bien
			if (matching_parentheses(tokens, start, end))
				return (parse_command_line(tokens, start + 1, end - 1));
		}
	}
	
	// Chercher opérateur de plus basse précédence
	op_pos = find_lowest_precedence_op(tokens, start, end);
	if (op_pos == -1)
	{
		// Traiter le cas sous-shell
		start_token = get_token_at_index(tokens, start);
		if (start_token && start_token->type == PAREN_OPEN && start < end)
		{
			closing = find_matching_parenthesis(tokens, start, end);
			if (closing > start && closing <= end)
				return (create_subshell_node(parse_command_line(tokens,
							start + 1, closing - 1)));
		}
		return (parse_simple_command(tokens, start, end));
	}
	
	// Créer nœud opérateur
	op_token = get_token_at_index(tokens, op_pos);
	if (!op_token)
		return (NULL);
		
	if (op_token->type == PIPE)
		node_type = AST_PIPE;
	else if (op_token->type == AND)
		node_type = AST_AND;
	else if (op_token->type == OR)
		node_type = AST_OR;
	else
		return (parse_simple_command(tokens, start, end));
		
	node = create_operator_node(node_type,
			parse_command_line(tokens, start, op_pos - 1),
			parse_command_line(tokens, op_pos + 1, end));
	return (node);
}