/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:59:12 by pitran            #+#    #+#             */
/*   Updated: 2025/03/06 14:24:11 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int find_token_len(char *content, token_type type)
{
	int	i;

	i = 0;
	switch (type)
	{
		case WORD:
		while (is_command_char(content[i]))
			i++;	
	}
	return (i);
}

int	find_command_len(char *word)
{
	int	len;

	len = 0;
	while (is_command_char(*word))
		len++;
	return (len);
}

