/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:30:41 by pitran            #+#    #+#             */
/*   Updated: 2025/04/10 14:04:44 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Forward declaration */
t_ast_node *parse_expression(t_token **token_list, int start, int end);

/* Main function to create AST from token list */
t_ast_node *create_ast(t_token **token_list)
{
    if (!token_list || !*token_list)
        return (NULL);
    
    /* Start recursive parsing from the full token list */
    return (parse_expression(token_list, 0, count_tokens(token_list) - 1));
}

/* Parse expressions with precedence: OR > AND > PIPE > COMMAND */
t_ast_node *parse_expression(t_token **token_list, int start, int end)
{
    int         i;
    t_token     *current;
    t_ast_node  *node;
    
    /* Handle empty or invalid range */
    if (start > end || start < 0)
        return (NULL);
    
    /* Look for OR operator (lowest precedence) */
    i = end;
    while (i >= start)
    {
        current = get_token_at_index(token_list, i);
        if (current && current->type == OR && !is_in_subshell(token_list, i))
        {
            node = create_ast_node(AST_OR);
            if (!node)
                return (NULL);
            node->left = parse_expression(token_list, start, i - 1);
            node->right = parse_expression(token_list, i + 1, end);
            return (node);
        }
        i--;
    }
    
    /* Look for AND operator */
    i = end;
    while (i >= start)
    {
        current = get_token_at_index(token_list, i);
        if (current && current->type == AND && !is_in_subshell(token_list, i))
        {
            node = create_ast_node(AST_AND);
            if (!node)
                return (NULL);
            node->left = parse_expression(token_list, start, i - 1);
            node->right = parse_expression(token_list, i + 1, end);
            return (node);
        }
        i--;
    }
    
    /* Look for PIPE operator */
    i = end;
    while (i >= start)
    {
        current = get_token_at_index(token_list, i);
        if (current && current->type == PIPE && !is_in_subshell(token_list, i))
        {
            node = create_ast_node(AST_PIPE);
            if (!node)
                return (NULL);
            node->left = parse_expression(token_list, start, i - 1);
            node->right = parse_expression(token_list, i + 1, end);
            return (node);
        }
        i--;
    }
    
    /* Handle subshell (parentheses) */
    current = get_token_at_index(token_list, start);
    if (current && current->type == PAREN_OPEN)
    {
        int matching_close = find_matching_paren(token_list, start);
        if (matching_close > 0 && matching_close <= end)
        {
            /* For subshells, create a subshell node */
            node = create_ast_node(AST_SUBSHELL);
            if (!node)
                return (NULL);
            
            /* Parse the expression inside parentheses */
            node->left = parse_expression(token_list, start + 1, matching_close - 1);
            
            /* If there's more after the closing parenthesis, it should be a pipe or other operator */
            if (matching_close < end)
            {
                /* Handle the case where a command follows the subshell without an explicit operator */
                /* In a real shell, this would be an error, but we can handle it gracefully */
                t_ast_node *parent_node = node;
                t_token *next_token = get_token_at_index(token_list, matching_close + 1);
                
                if (next_token && (next_token->type == PIPE || next_token->type == AND || next_token->type == OR))
                {
                    /* Let the next iteration handle this */
                    return (node);
                }
                else
                {
                    /* Treat as an implicit pipe (this is an approximation) */
                    printf("Warning: Command after subshell without operator, assuming pipe\n");
                    t_ast_node *pipe_node = create_ast_node(AST_PIPE);
                    if (!pipe_node)
                    {
                        free_ast_node(node);
                        return (NULL);
                    }
                    pipe_node->left = node;
                    pipe_node->right = parse_expression(token_list, matching_close + 1, end);
                    return (pipe_node);
                }
            }
            return (node);
        }
    }
    
    /* Base case: simple command */
    return (create_command_node(token_list, start, end));
}