/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:34:09 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 13:13:25 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ast_node	*create_command_node(char **args)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->data.command.args = args;
	node->data.command.redirections = NULL;                                                                            
	return (node);
}

t_ast_node	*create_operator_node(t_node_type type, t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->data.binary.left = left;
	node->data.binary.right = right;
	return (node);
}

t_ast_node	*create_subshell_node(t_ast_node *child)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->data.subshell.child = child;
	return (node);
}

t_redirection	*create_redirection(t_redir_type type, char *file)
{
	t_redirection	*redir;

	redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

void	add_redirection(t_ast_node *cmd_node, t_redirection *redir)
{
	t_redirection	*current;

	if (!cmd_node || !redir || cmd_node->type != NODE_COMMAND)
		return ;
	if (!cmd_node->data.command.redirections)
	{
		cmd_node->data.command.redirections = redir;
		return ;
	}
	current = cmd_node->data.command.redirections;
	while (current->next)
		current = current->next;
	current->next = redir;
}
