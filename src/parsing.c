/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/20 08:29:44 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// Função para dividir a linha de comando em comando e argumentos
char	**parse_command(char *input)
{
	char	**args;
	char	*arg;
	int		i;

	args = (char **)malloc(64 * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	arg = ft_strtok(input, " ");
	while (arg)
	{
		args[i++] = arg;
		arg = ft_strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
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
		int x = 0;
		if (ft_strchr(input, '<') || ft_strchr(input, '>'))
		{
			handle_redirections(args);
			x=1;
		}
		command = args[x];
		execute_path(command, args, env);
		free(args);
	}
}


