/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/06 09:02:16 by ruidos-s         ###   ########.fr       */
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


void	handle_command(char *input, char **env)
{
	char	**args;
	char	*command;

	args = parse_command(input);
	if (!args)
		return ;
	command = args[0];
	execute_path(command, args, env);
	free(args);
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
			handle_command(input, env);
		free(input);
		input = get_command_input();
	}
	rl_clear_history();
	return (0);
}

/* int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*command;
	char	**args;
	char	*executable;

	(void) ac;
	(void) av;
	while ((input = readline("Minishell: ")) != NULL)
	{
		if (*input)
		{
			add_history(input);

			args = parse_command(input);
			if (!args)
			{
				free(input);
				continue ;
			}
			command = args[0];
            // Verificar se é um caminho absoluto, relativo ou só o nome do executável
			if (command[0] == '/' || command[0] == '.')
			{
                // Caminho absoluto ou relativo
				if (access(command, X_OK) == 0)
				{
					execute_command(command, args, env);
				}
				else
				{
					write(STDERR_FILENO, "Command not found\n", 18);
				}
			}
			else
			{
                // Procurar no PATH
				executable = find_executable(command);
				if (executable)
				{
					execute_command(executable, args, env);
					free(executable);
				}
				else
				{
					write(STDERR_FILENO, "Command not found in PATH\n", 26);
				}
			}

			free(args);
		}
		free(input);
	}

	rl_clear_history();
	return (0);
}
 */