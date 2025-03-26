/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:00:43 by pitran            #+#    #+#             */
/*   Updated: 2025/03/26 15:44:27 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *read_command()
{
    char *command;

    while (1)
    {
        command = readline ("Minishell >");
        if (command)
            add_history(command);
        else
            break;
    }
    return (command);
}

int main()
{
    parse_input();

}

/*
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


MAIN

int main()
{
	parse_input(command)
	execute
}*/