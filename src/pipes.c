/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/09 14:13:45 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_piped_commands(char ***commands, char **env)
{
	int		fd[2];
	pid_t	pid;
	int		i = 0;
	int		in_fd = 0;

	while (commands[i])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(in_fd, STDIN_FILENO); // Entrada do pipe anterior
			if (commands[i + 1])
				dup2(fd[1], STDOUT_FILENO); // Saída para o próximo pipe
			close_fds(fd);
			handle_redirections(commands[i]); // Tratar redirecionamentos dentro de cada comando
			execute_path(commands[i][0], commands[i], env);
			//perror("execve error");
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			perror("fork error");
		else
		{
			wait(NULL);
			close(fd[1]);
			in_fd = fd[0]; // Guardar a entrada para o próximo comando
			i++;
		}
	}
}

char	***split_by_pipe(char *input)
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