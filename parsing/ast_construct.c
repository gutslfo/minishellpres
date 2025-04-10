/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_construct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:30:41 by pitran            #+#    #+#             */
/*   Updated: 2025/04/10 14:04:14 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Helper function to get token at specific index */
t_token *get_token_at_index(t_token **token_list, int index)
{
    t_token *current;
    int     i;

    if (!token_list || !*token_list)
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

/* Check if token at index is inside parentheses */
int is_in_subshell(t_token **token_list, int index)
{
    int     i;
    int     paren_level;
    t_token *current;

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

/* Find matching closing parenthesis */
int find_matching_paren(t_token **token_list, int open_index)
{
    int     paren_level;
    int     i;
    t_token *current;
    
    paren_level = 1;
    i = open_index + 1;
    
    while (1)
    {
        current = get_token_at_index(token_list, i);
        if (!current)
            return (-1);
        
        if (current->type == PAREN_OPEN)
            paren_level++;
        else if (current->type == PAREN_CLOSE)
        {
            paren_level--;
            if (paren_level == 0)
                return (i);
        }
        i++;
    }
}

/* Extract command arguments from token sequence */
char **extract_command_args(t_token **token_list, int start, int end)
{
    int     arg_count;
    int     i;
    t_token *current;
    char    **args;
    
    /* Count WORD tokens in range */
    arg_count = 0;
    i = start;
    while (i <= end)
    {
        current = get_token_at_index(token_list, i);
        if (current && current->type == WORD)
            arg_count++;
        i++;
    }
    
    /* Allocate args array with NULL terminator */
    args = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!args)
        return (NULL);
    
    /* Fill args array */
    arg_count = 0;
    i = start;
    while (i <= end)
    {
        current = get_token_at_index(token_list, i);
        if (current && current->type == WORD)
        {
            args[arg_count] = strdup(current->content);
            arg_count++;
        }
        i++;
    }
    args[arg_count] = NULL;
    
    return (args);
}

/* Extract redirections from token sequence */
t_token **extract_redirections(t_token **token_list, int start, int end, int *count)
{
    int     redir_count;
    int     i;
    t_token *current;
    t_token **redirs;
    
    /* Count redirection tokens in range */
    redir_count = 0;
    i = start;
    while (i <= end)
    {
        current = get_token_at_index(token_list, i);
        if (current && (current->type == REDIR_IN || current->type == REDIR_OUT || 
                        current->type == REDIR_APPEND || current->type == HEREDOC))
            redir_count++;
        i++;
    }
    
    *count = redir_count;
    if (redir_count == 0)
        return (NULL);
    
    /* Allocate redirections array */
    redirs = (t_token **)malloc(sizeof(t_token *) * redir_count);
    if (!redirs)
        return (NULL);
    
    /* Fill redirections array */
    redir_count = 0;
    i = start;
    while (i <= end)
    {
        current = get_token_at_index(token_list, i);
        if (current && (current->type == REDIR_IN || current->type == REDIR_OUT || 
                        current->type == REDIR_APPEND || current->type == HEREDOC))
        {
            redirs[redir_count] = current;
            redir_count++;
        }
        i++;
    }
    
    return (redirs);
}

/* Create a command node from token range */
t_ast_node *create_command_node(t_token **token_list, int start, int end)
{
    t_ast_node *node;
    
    node = create_ast_node(AST_COMMAND);
    if (!node)
        return (NULL);
    
    /* Extract command arguments */
    node->args = extract_command_args(token_list, start, end);
    
    /* Extract redirections */
    node->redirs = extract_redirections(token_list, start, end, &node->redirs_count);
    
    return (node);
}