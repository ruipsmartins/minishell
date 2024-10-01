/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/01 12:42:45 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_piped_commands(t_command *cmd, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd = 0; // Ficheiro de entrada do comando anterior

	while (cmd != NULL)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			// No processo filho
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO); // Entrada do pipe anterior
				close(in_fd);
			}
			if (cmd->next != NULL)
			{
				dup2(fd[1], STDOUT_FILENO); // Saída para o próximo pipe
				close(fd[0]); // Fechar a leitura do pipe atual no processo filho
			}
			close(fd[1]); // Fechar a escrita do pipe

			// Tratar redirecionamentos se necessário
			/* if (handle_redirects(cmd, NULL, NULL) == -1)
				exit(EXIT_FAILURE); */

			// Executar o comando
			execute_command(cmd->args[0], cmd->args, env);

			perror("execve error"); // Se o execve falhar
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		else
		{
			// No processo pai
			wait(NULL); // Esperar que o processo filho termine
			close(fd[1]); // Fechar o descritor de escrita no pai
			in_fd = fd[0]; // Guardar a leitura para o próximo comando
			cmd = cmd->next; // Avançar para o próximo comando na pipeline
		}
	}
}

/* char	***split_by_pipe(char *input)
{
	char	**pipe_segments = malloc(64 * sizeof(char *));
	char	***commands = malloc(64 * sizeof(char **));
	char	*segment;
	int		i = 0;
	int		j = 0;

	segment = ft_strtok(input, "|");
	while (segment)
	{
		pipe_segments[i++] = segment;
		segment = ft_strtok(NULL, "|");
	}
	pipe_segments[i] = NULL;
	while (pipe_segments[j])
	{
		commands[j] = parse_command(pipe_segments[j]);
		j++;
	}
	commands[i] = NULL;
	free(pipe_segments);
	return (commands);
}
 */