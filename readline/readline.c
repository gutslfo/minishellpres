/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:00:43 by pitran            #+#    #+#             */
/*   Updated: 2025/03/06 14:35:38 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(void)
{
	char    *command;

	while (1)
	{
		command = readline("Minishell > ");
		if (command)
			add_history(command);
		else
			break;
		//execute_command(command);
	}
}

/*MAIN

int main()
{
	parse_input(command)
	execute
}*/