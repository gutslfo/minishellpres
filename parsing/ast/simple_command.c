/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:00:00 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 17:05:00 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h> /* Pour strdup */

int	is_redirection_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == REDIR_IN)
		return (REDIR_TYPE_IN);
	else if (type == REDIR_OUT)
		return (REDIR_TYPE_OUT);
	else if (type == REDIR_APPEND)
		return (REDIR_TYPE_APPEND);
	else if (type == HEREDOC)
		return (REDIR_TYPE_HEREDOC);
	return (REDIR_TYPE_IN);
}

int count_args(t_token **tokens, int start, int end)
{
    int count;
    int i;
    t_token *current;

    count = 0;
    i = start;
    current = NULL;
    
    // Get the head of the token list
    if (tokens && *tokens)
        current = *tokens;
    
    // Advance to the start position
    for (int j = 0; current && j < start; j++)
        current = current->next;
    
    // Count the args
    while (current && i <= end)
    {
        if (current->type == WORD)
            count++;
        else if (is_redirection_token(current->type))
            i++; // Skip the next token which should be the redirection target
        
        current = current->next;
        i++;
    }
    return (count);
}

char **extract_args(t_token **tokens, int start, int end)
{
    char **args;
    int count;
    t_token *current;
    int arg_idx;
    int i;

    count = count_args(tokens, start, end); // Assuming count_args works correctly
    args = (char **)malloc(sizeof(char *) * (count + 1));
    if (!args)
        return (NULL);
    
    current = *tokens; // Start at the head of the list
    
    // Advance to the start position
    i = 0;
    while (current && i < start)
    {
        current = current->next;
        i++;
    }
    arg_idx = 0;
    while (current && i <= end && arg_idx < count)
    {
        if (current->type == WORD)
        {
            args[arg_idx] = strdup(current->content);
            arg_idx++;
        }
        else if (is_redirection_token(current->type)) // Skip the next token if it's a redirection
        {
            current = current->next; // Skip the redirection target
            i++;
            if (!current) // Check if we reached the end
                break;
        }
        
        current = current->next;
        i++;
    }
    args[arg_idx] = NULL; // Terminate with NULL
    return (args);
}

void extract_redirections(t_ast_node *node, t_token **tokens, int start, int end)
{
    t_redirection *redir;
    t_token *current;
    int i;

    if (!node || !tokens || !*tokens || node->type != AST_COMMAND)
        return;

    // Start at the head of the list
    current = *tokens;
    
    // Advance to the start position
    i = 0;
    while (current && i < start)
    {
        current = current->next;
        i++;
    }
    
    // Process each token in the range
    while (current && i <= end)
    {
        if (is_redirection_token(current->type))
        {
            // Check if next token exists and is a WORD
            if (current->next && current->next->type == WORD)
            {
                redir = create_redirection(token_to_redir_type(current->type),
                                       strdup(current->next->content));
                if (redir)
                    add_redirection(node, redir);
                
                // Skip the next token (the redirection target)
                current = current->next;
                i++;
            }
        }
        
        // Move to the next token
        current = current->next;
        i++;
    }
}

t_ast_node	*parse_simple_command(t_token **tokens, int start, int end)
{
	t_ast_node	*node;
	char		**args;

	if (start < 0 || end < 0 || start > end)
		return (NULL);
		
	// Vérifier qu'il y a au moins un token valide dans la plage
	if (!get_token_at_index(tokens, start))
		return (NULL);
		
	args = extract_args(tokens, start, end);
	if (!args)
		return (NULL);
		
	// Vérifier que nous avons au moins un argument
	if (!args[0])
	{
		free_string_array(args);
		return (NULL);
	}
	
	node = create_command_node(args);
	if (!node)
	{
		free_string_array(args);
		return (NULL);
	}
	
	extract_redirections(node, tokens, start, end);
	return (node);
}