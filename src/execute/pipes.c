/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/04 12:35:40 by ruidos-s         ###   ########.fr       */
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
bool	should_execute_in_parent(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0 || ft_strncmp(cmd->args[0],
			"unset", 6) == 0 || ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
	{
		if (cmd->args[1] != NULL)
			return (true);
		return (false);
	}
	return (false);
}

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}
void	close_all_pipes(int **fds, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

void	free_pipes(int **fds, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(fds[i]);
		i++;
	}
	free(fds);
}

void	fork_error(void)
{
	perror("fork error:");
	exit(EXIT_FAILURE);
}

/* Função para executar comandos em sequência,
utilizando pipes para a comunicação entre processos. */
void	execute_piped_commands(t_command *cmd, t_data *data)
{
	int	i;
	int	j;

	data->cmd_count = count_commands(cmd); // Número de comandos no pipeline
	int **fds;                           // Array de pipes
	pid_t *pids;                         // Array de PIDs
	i = 0;
	// Alocar memória para os pipes e PIDs
	fds = malloc(sizeof(int *) * (data->cmd_count - 1));
	pids = malloc(sizeof(pid_t) * data->cmd_count);
	while (i < data->cmd_count - 1)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (pipe(fds[i]) < 0)
			perror("pipe");
		i++;
	}
	i = 0;
	while (cmd != NULL)
	{
		if (builtin_checker(cmd) && should_execute_in_parent(cmd))// Builtin no pai
		{
			builtin_execute(cmd, data);
		}
		else // Processo filho
		{
			pids[i] = fork();
			if (pids[i] < 0)
				perror("fork");
			else if (pids[i] == 0)
			{
				// Configura os FDs para o processo filho
				if (i > 0)
					dup2(fds[i - 1][0], STDIN_FILENO); // Lê do pipe anterior
				if (cmd->next != NULL)
					dup2(fds[i][1], STDOUT_FILENO); // Escreve no próximo pipe
				// Fecha todos os FDs nos filhos
				close_all_pipes(fds, data->cmd_count - 1);
				if (handle_redirects(cmd, data) == -1)
					exit(EXIT_FAILURE);
				// Executa o comando
				if (builtin_execute(cmd, data))
					exit(data->return_value);
				execute_command_or_path(cmd, data);
				exit(data->return_value);
			}
		}
		// Fecha os pipes desnecessários no pai
		if (i > 0)
		{
			close(fds[i - 1][0]);
			close(fds[i - 1][1]);
		}
		cmd = cmd->next;
		i++;
	}
	// Fecha todos os FDs restantes no pai
	close_all_pipes(fds, data->cmd_count - 1);
	// Espera por todos os processos filhos
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &data->return_value, 0); //ver quando só tem um comando
		if (WIFEXITED(data->return_value))
			data->return_value = WEXITSTATUS(data->return_value);
		j++;
	}
	// Liberta memória
	free_pipes(fds, data->cmd_count - 1);
	free(pids);
}
