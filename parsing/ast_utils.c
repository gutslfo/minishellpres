/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:30:41 by pitran            #+#    #+#             */
/*   Updated: 2025/04/10 14:03:23 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Create a new AST node of the specified type */
t_ast_node *create_ast_node(t_ast_type type)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirs = NULL;
	node->redirs_count = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* Free an AST node and all its children recursively */
void free_ast_node(t_ast_node *node)
{
	int i;

	if (!node)
		return;
	free_ast_node(node->left);
	free_ast_node(node->right);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->redirs)
		free(node->redirs);
	free(node);
}

/* Print the AST for debugging (recursive) */
void print_ast(t_ast_node *node, int depth)
{
	int i;

	i = 0;
	if (!node)
		return;
	
	/* Print indentation based on depth */
	while (i < depth; i++)
	{
		printf("  ");
		i++;
	}
	
	/* Print node type and content */
	if (node->type == AST_COMMAND)
	{
		printf("COMMAND: ");
		if (node->args)
		{
			i = 0;
			while (node->args[i])
			{
				printf("%s ", node->args[i]);
				i++;
			}
		}
		printf("\n");
		
		/* Print redirections if any */
		if (node->redirs && node->redirs_count > 0)
		{
			for (i = 0; i < depth + 1; i++)
				printf("  ");
			printf("REDIRECTIONS: %d\n", node->redirs_count);
		}
	}
	else if (node->type == AST_PIPE)
		printf("PIPE |\n");
	else if (node->type == AST_AND)
		printf("AND &&\n");
	else if (node->type == AST_OR)
		printf("OR ||\n");
	else if (node->type == AST_SUBSHELL)
		printf("SUBSHELL ()\n");
	
	/* Print children */
	if (node->left)
		print_ast(node->left, depth + 1);
	if (node->right)
		print_ast(node->right, depth + 1);
}
