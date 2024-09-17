/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/17 10:51:17 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command_input(void)
{
	char	*input;

	input = readline("Minishell: ");
	if (input && *input)
		add_history(input);
	return (input);
}


int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	input = get_command_input();
	while (input != NULL)
	{
		if (*input)
			handle_input(input, env);
		free(input);
		input = get_command_input();
	}
	free(input);
	printf("test\n");
	rl_clear_history();
	return (0);
}
