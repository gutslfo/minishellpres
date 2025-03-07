/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:37:08 by pitran            #+#    #+#             */
/*   Updated: 2025/03/07 16:27:28 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*tokenize_special_caracter(char *command, t_token *token)
{
	int	len;
	int	i;
	
	len = 1;
	define_special_caracter(command, token);
	token->content = (char *)malloc(sizeof(char) * len +1);
	if (!token->content)
		return (NULL);
	i = 0;
	token->content[i] = command[i];
	token->content[i++] = '\0';
	return (&command[i++]);
}
void	define_special_caracter(char *command, t_token *token)
{
	if (*(command) == '$')
	{
		if (is_command_char(*(command)++))
			token->type = ENV_VAR;
		else if ((*command)++ == '?')
			token->type = EXIT_STATUS;
		else
			token->type = UNKNOWN;
	}
	else if (*(command) == '\\')
		token->type = ESCAPE;
	else if (*(command) == '#')
		token->type = COMMENT;
	else if (*(command) == '\n')
		token->type = T_NEWLINE;
	else if (*(command) == '\0')
		token->type = T_EOF;
}

void	define_double_redirection(char *command, t_token *token, int *len)
{
	if (*(command) == '>' && *(command)++ == '>')
		token->type = REDIR_APPEND;
	else if (*(command) == '<' && *(command)++ == '<')
		token->type = HEREDOC;
	else 
		token->type = UNKNOWN;
	*(len) = 2;
}

void	define_bonus_operator(char *command, t_token *token, int *len)
{
	if (*(command) == '&' && *(command)++ == '&')
		token->type = AND;
	else if (*(command) == '|' && *(command)++ == '|')
		token->type = OR;
	else
		token->type = UNKNOWN;
	*(len) = 2;
}
