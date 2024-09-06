/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/06 11:36:28 by ruidos-s         ###   ########.fr       */
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


void	handle_input(char *input, char **env)
{
	char	**args;
	char	*command;
	char	***commands;
	int		i;

	if (ft_strchr(input, '|'))
	{
		commands = split_by_pipe(input);
		execute_piped_commands(commands, env);
		i = 0;
		// Liberação de memória dos comandos
		while (commands[i])
		{
			free(commands[i]);
			i++;
		}
		free(commands);
	}
	else
	{
		args = parse_command(input);
		if (!args)
			return ;
		command = args[0];
		execute_path(command, args, env);
		free(args);
	}
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
	rl_clear_history();
	return (0);
}
