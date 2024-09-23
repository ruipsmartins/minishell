/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/23 16:45:46 by ruidos-s         ###   ########.fr       */
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
	t_commands cmd;
	char	*command;
	int		i;

	// Guardar a linha de input original
	cmd.input = strdup(input);

	if (ft_strchr(input, '|'))
	{
		// Se houver pipes, dividimos o input em comandos
		cmd.commands = split_by_pipe(input);
		execute_piped_commands(cmd.commands, env);

		// Liberação de memória dos comandos
		i = 0;
		while (cmd.commands[i])
		{
			free(cmd.commands[i]);
			i++;
		}
		free(cmd.commands);
	}
	else
	{
		// Se não houver pipes, apenas guardamos os argumentos
		cmd.args = parse_command(input);
		if (!cmd.args)
			return;

		// Verificar redirecionamentos
		int x = 0;
		if (ft_strchr(input, '<') || ft_strchr(input, '>'))
		{
			handle_redirections(cmd.args);
			x = 1;
		}

		// O comando será o primeiro argumento
		command = cmd.args[x];
		execute_path(command, cmd.args, env);

		// Liberação de memória dos argumentos
		free(cmd.args);
	}

	// Liberação de memória do input original guardado na estrutura
	free(cmd.input);
}

