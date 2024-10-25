/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/25 11:23:28 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para lidar com os file descriptors (FDs) (comunicação entre pipes).
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
int	ft_child(int in_fd, t_command *cmd, int fd[2], t_data *data,
		int exit_pipe[2])
{
	close(exit_pipe[0]);
	if (ft_strncmp(cmd->args[0], "exit", 5))
	{
		if (handle_redirects(cmd, data) == -1)
			exit(EXIT_FAILURE);
		handle_fd(in_fd, cmd, fd);
	}
	execute_command_or_path(cmd, data);
	std_reset(&data->original_stdin, &data->original_stdout);
	if (data->close_shell)
	{
		write(exit_pipe[1], "1", 1);
	}
	close(exit_pipe[1]);
	exit(EXIT_SUCCESS);
}

bool	ft_parent(int *in_fd, int fd[2], t_data *data, int exit_pipe[2])
{
	char	exit_signal;

	close(fd[1]); // Fecha a extremidade de escrita do pipe
	close(exit_pipe[1]);
	if (read(exit_pipe[0], &exit_signal, 1) > 0 && exit_signal == '1')
	{
		data->close_shell = true;
		return (true);
	}
	*in_fd = fd[0]; // Prepara para o próximo comando
	return (false);
}

/* Função para executar comandos em sequência,
utilizando pipes para a comunicação entre processos. */
void	execute_piped_commands(t_command *cmd, t_data *data)
{
	pid_t	pid;
	int		in_fd;
	int		fd[2];
	int		exit_pipe[2];

	in_fd = 0;
	while (cmd != NULL)
	{
		pipe(fd);
		pipe(exit_pipe);
		pid = fork();
		if (pid < 0)
		{
			perror("fork error:");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			ft_child(in_fd, cmd, fd, data, exit_pipe);
		else
		{
			if (ft_parent(&in_fd, fd, data, exit_pipe))
				break ;       // Sai do loop se 'exit' foi encontrado
			cmd = cmd->next; // Avança para o próximo comando
		}
	}
}
