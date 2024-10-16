/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/17 16:40:16 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para lidar com os file descriptors (FDs) no processo filho.
void	handle_fd(int in_fd, t_command *cmd, int fd[2])
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next != NULL)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	close(fd[1]);
}

// Função para executar o comando no processo filho.
void	ft_child(int in_fd, t_command *cmd, int fd[2], t_data *data)
{
	if (handle_redirects(cmd, data) == -1)
		exit(EXIT_FAILURE);
	handle_fd(in_fd, cmd, fd);
	execute_command_or_path(cmd, data);
	std_reset(&data->original_stdin, &data->original_stdout);
	exit(EXIT_FAILURE);
}

/* Função para executar comandos em sequência,
utilizando pipes para a comunicação entre processos. */
void	execute_piped_commands(t_command *cmd, t_data *data)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd;

	in_fd = 0;
	while (cmd != NULL)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
			ft_child(in_fd, cmd, fd, data);
		else if (pid < 0)
		{
			perror("fork error:");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			in_fd = fd[0];
			cmd = cmd->next;
		}
	}
}
