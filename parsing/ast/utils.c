/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:40:29 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 15:19:25 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_ast_node(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
	{
		free_string_array(node->data.command.args);
		free_redirections(node->data.command.redirections);
	}
	else if (node->type == AST_PIPE || node->type == AST_AND
		|| node->type == AST_OR)
	{
		free_ast_node(node->data.binary.left);
		free_ast_node(node->data.binary.right);
	}
	else if (node->type == AST_SUBSHELL)
	{
		free_ast_node(node->data.subshell.child);
	}
	free(node);
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_redirections(t_redirection *redirections)
{
	t_redirection	*current;
	t_redirection	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
}

void	print_ast(t_ast_node *node, int depth)
{
	int	i;
	int	j;

	if (!node)
		return ;
	for (i = 0; i < depth; i++)
		printf("  ");
	if (node->type == AST_COMMAND)
	{
		printf("COMMAND: ");
		j = 0;
		while (node->data.command.args && node->data.command.args[j])
		{
			printf("%s ", node->data.command.args[j]);
			j++;
		}
		printf("\n");
		print_redirections(node->data.command.redirections, depth + 1);
	}
	else if (node->type == AST_PIPE)
		printf("PIPE |\n");
	else if (node->type == AST_AND)
		printf("AND &&\n");
	else if (node->type == AST_OR)
		printf("OR ||\n");
	else if (node->type == AST_SUBSHELL)
		printf("SUBSHELL ()\n");
	if (node->type == AST_PIPE || node->type == AST_AND || node->type == AST_OR)
	{
		print_ast(node->data.binary.left, depth + 1);
		print_ast(node->data.binary.right, depth + 1);
	}
	else if (node->type == AST_SUBSHELL)
	{
		print_ast(node->data.subshell.child, depth + 1);
	}
}

void	print_redirections(t_redirection *redirections, int depth)
{
	t_redirection	*current;
	int				i;

	current = redirections;
	while (current)
	{
		for (i = 0; i < depth; i++)
			printf("  ");
		printf("REDIRECTION: ");
		if (current->type == REDIR_TYPE_IN)
			printf("< ");
		else if (current->type == REDIR_TYPE_OUT)
			printf("> ");
		else if (current->type == REDIR_TYPE_APPEND)
			printf(">> ");
		else if (current->type == REDIR_TYPE_HEREDOC)
			printf("<< ");
		printf("%s\n", current->file);
		current = current->next;
	}
}