/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:00:23 by pitran            #+#    #+#             */
/*   Updated: 2025/03/07 16:20:48 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_token    **tokenize_input(char *command)
{
	t_token		**token_list;
	token_type	type;

	token_list = NULL;
	type = DEFAULT;
	while (*command)
	{
		if (is_command_char(*command))
			type = WORD;
		else if (is_quote(*command))
			type = QUOTE;
		else if (is_redirection(*command))
			type = REDIR;
		else if (is_operator(*command))
			type = OPERATOR;
		else if (is_parenthesis(*command))
			type = PARENTHESIS;
		else if (is_special_caracter(*command))
			type = SPECIAL_CARACTER;
		command = extract_token(command, type, token_list);
	}
	return (token_list);
}

char	*extract_token(char *command, token_type type, t_token **token_list)
{
	char *pointer;
	t_token *new_token;
	
	if (!*(command) || !command || type == DEFAULT)
		return (NULL);
	new_token = NULL;
	new_token = create_token(new_token);
	if (!new_token)
		return (NULL);//Message d'erreur
	pointer = handle_token_type(command, type, new_token);
	link_token(new_token, token_list);
	return (pointer);
}

char	*handle_token_type(char *command, token_type type, t_token *new_token)
{
	char *pointer;
	switch (type)
	{
		case WORD:
		pointer = tokenize_word(command, new_token);
		break;
		case QUOTE:
		pointer = tokenize_quote(command, new_token);
		break;
		case REDIR:
		pointer = tokenize_redir(command, new_token);
		break;
		case OPERATOR: 
		pointer = tokenize_operator(command, new_token);
		break;
		case PARENTHESIS:
		pointer = tokenize_parenthesis(command, new_token);
		break;
		case SPECIAL_CARACTER:
		pointer = tokenize_special_caracter(command, new_token);
		break;
		default:
		break;
	}
	return (pointer);
}

