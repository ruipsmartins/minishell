/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/27 15:00:31 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

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
int	ft_child(int in_fd, t_command *cmd, t_data *data)
{
	close(data->exit_pipe[0]);
	data->return_value = 0;
	if (ft_strncmp(cmd->args[0], "exit", 5))
	{
		if (handle_redirects(cmd, data) == -1)
			exit(EXIT_FAILURE);
		handle_fd(in_fd, cmd, data->fd);
	}
	if (builtin_execute(cmd, data) == false)
		execute_command_or_path(cmd, data);
	std_reset(&data->original_stdin, &data->original_stdout); // Restaura os FDs
	if (data->close_shell)
		// Se o comando for 'exit', fecha o shell
		write(data->exit_pipe[1], "1", 1);
	close(data->exit_pipe[1]);
	exit(data->return_value);
}

bool	ft_parent(t_command *cmd, int *in_fd, t_data *data)
{
	char	exit_signal;
	int		status;

	close(data->fd[1]); // Fecha a extremidade de escrita do pipe
	close(data->exit_pipe[1]);
	waitpid(-1, &status, 0); // Espera pelo processo filho e recebe o status
	if (read(data->exit_pipe[0], &exit_signal, 1) > 0 && exit_signal == '1')
	{
		data->close_shell = true;
		return (true);
	}
	if (WIFEXITED(status))
		// Se o filho terminou normalmente
		data->return_value = WEXITSTATUS(status);
	// Guarda o valor de saída do filho em `data->return_value`
	else
		data->return_value = 0;
	*in_fd = data->fd[0]; // Prepara para o próximo comando
	if (builtin_checker(cmd) == true)
		builtin_execute(cmd, data);
	return (false);
}

/* Função para executar comandos em sequência,
utilizando pipes para a comunicação entre processos. */
void	execute_piped_commands(t_command *cmd, t_data *data)
{
	pid_t	pid;
	int		in_fd;

	in_fd = 0;
	while (cmd != NULL)
	{
		pipe(data->fd);
		pipe(data->exit_pipe);
		pid = fork();
		if (pid < 0)
			fork_error();
		else if (pid == 0)
		{
			if (builtin_checker(cmd) == true)
				exit(data->return_value);
			ft_child(in_fd, cmd, data);
		}
		else
		{
			if (ft_parent(cmd, &in_fd, data))
				break ;       // Sai do loop se 'exit' foi encontrado
			cmd = cmd->next; // Avança para o próximo comando
		}
	}
}

void	fork_error(void)
{
	perror("fork error:");
	exit(EXIT_FAILURE);
}
