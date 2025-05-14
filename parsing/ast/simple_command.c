/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:00:00 by pitran            #+#    #+#             */
/*   Updated: 2025/05/14 16:22:00 by pitran           ###   ########.fr       */
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

int	count_args(t_token **tokens, int start, int end)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (i <= end)
	{
		if (tokens[i]->type == WORD)
			count++;
		else if (is_redirection_token(tokens[i]->type))
			i++;
		i++;
	}
	return (count);
}

char	**extract_args(t_token **tokens, int start, int end)
{
	char	**args;
	int		count;
	int		i;
	int		arg_idx;

	count = count_args(tokens, start, end);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = start;
	arg_idx = 0;
	while (i <= end && arg_idx < count)
	{
		if (tokens[i]->type == WORD)
		{
			args[arg_idx] = strdup(tokens[i]->content);
			arg_idx++;
		}
		else if (is_redirection_token(tokens[i]->type))
			i++;
		i++;
	}
	args[arg_idx] = NULL;
	return (args);
}

void	extract_redirections(t_ast_node *node, t_token **tokens,
	int start, int end)
{
	t_redirection	*redir;
	int				i;

	i = start;
	while (i <= end)
	{
		if (is_redirection_token(tokens[i]->type) && i + 1 <= end
			&& tokens[i + 1]->type == WORD)
		{
			redir = create_redirection(token_to_redir_type(tokens[i]->type),
					strdup(tokens[i + 1]->content));
			if (redir)
				add_redirection(node, redir);
			i++;
		}
		i++;
	}
}

t_ast_node	*parse_simple_command(t_token **tokens, int start, int end)
{
	t_ast_node	*node;
	char		**args;

	args = extract_args(tokens, start, end);
	if (!args)
		return (NULL);
	node = create_command_node(args);
	if (!node)
	{
		free_string_array(args);
		return (NULL);
	}
	extract_redirections(node, tokens, start, end);
	return (node);
}