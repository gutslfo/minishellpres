/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitran <pitran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:00:43 by pitran            #+#    #+#             */
/*   Updated: 2025/05/26 14:54:16 by pitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char	*command;

	(void)argc;
	(void)argv;
	t_shell_data shell = {envp, NULL, 0};
	while (1)
	{
		command = readline("Petit coquillage > ");
		if (!command)
			break ;
		if (*command)
		{
			add_history(command);
			parse_input(command);
		}
		free(command);
	}
	return (0);
}