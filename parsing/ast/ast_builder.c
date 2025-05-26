/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:30:21 by pitran            #+#    #+#             */
/*   Updated: 2025/05/26 16:26:41 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Crée l'AST principal à partir de la liste de tokens.
** Gère l'allocation du noeud racine, l'appel au parsing, et l'organisation
** de l'arbre selon le type de noeud retourné.
*/
t_ast	*create_ast(t_token **token_list, t_shell_data *shell )
{
	t_ast	*root;
	t_ast	*tree;
	int		token_count;

	if (!token_list || !*token_list)
		return (NULL);
	root = create_ast_node(NODE_CMD, NULL);
	if (!root)
		return (NULL);
	root->root = root;
	root->envp = shell->envp;
	token_count = count_tokens(token_list);
	tree = parse_command_line(token_list, 0, token_count - 1, root);
	if (!tree)
	{
		free_ast(root);
		return (NULL);
	}
	if (tree->type == NODE_CMD)
	{
		tree->root = tree;
		tree->envp = shell->envp;
		free(root);
		return (tree);
	}
	root->children = (t_ast **)malloc(sizeof(t_ast *) * 2);
	if (!root->children)
	{
		free_ast(tree);
		free_ast(root);
		return (NULL);
	}
	root->children[0] = tree;
	root->children[1] = NULL;
	return (root);
}

/*
** Récupère le token à l'index donné dans la liste chaînée de tokens.
*/
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

/*
** Vérifie si la séquence de tokens entre start et end est bien entourée
** par des parenthèses appariées et correctement imbriquées.
*/
int	matching_parentheses(t_token **tokens, int start, int end)
{
	int		level;
	int		i;
	t_token	*current;

	current = get_token_at_index(tokens, start);
	if (!current || current->type != PAREN_OPEN)
		return (0);
	current = get_token_at_index(tokens, end);
	if (!current || current->type != PAREN_CLOSE)
		return (0);
	level = 0;
	i = start;
	while (i <= end)
	{
		current = get_token_at_index(tokens, i);
		if (!current)
			break ;
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

/*
** Trouve l'index de la parenthèse fermante correspondant à la parenthèse
** ouvrante située à open_pos dans la liste de tokens.
** Retourne l'index de la parenthèse fermante ou -1 si non trouvée.
*/
int	find_matching_parenthesis(t_token **tokens, int open_pos, int end)
{
	int		level;
	int		i;
	t_token	*current;

	current = get_token_at_index(tokens, open_pos);
	if (!current || current->type != PAREN_OPEN)
		return (0);
	level = 1;
	i = open_pos + 1;
	while (i <= end)
	{
		current = get_token_at_index(tokens, i);
		if (!current)
			break ;
		if (current->type == PAREN_OPEN)
			level++;
		else if (current->type == PAREN_CLOSE)
		{
			level--;
			if (level == 0)
				return (i);
		}
		i++;
	}
	return (0);
}
