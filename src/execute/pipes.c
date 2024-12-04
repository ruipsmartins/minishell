/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/04 16:43:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

// Função para executar o comando no processo filho.
void	ft_child(int i, int **fds, t_command *cmd, t_data *data)
{
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

/* bool	ft_parent(t_command *cmd, int *in_fd, t_data *data)
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
} */

/* Função para executar comandos em sequência,
utilizando pipes para a comunicação entre processos. */
void	execute_piped_commands(t_command *cmd, t_data *data)
{
	int	i;
	int	j;

	data->cmd_count = count_commands(cmd); // Número de comandos no pipeline
	int **fds;                             // Array de pipes
	pid_t *pids;                           // Array de PIDs
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
		if (builtin_checker(cmd) && should_execute_in_parent(cmd))
			builtin_execute(cmd, data);
		else // Processo filho
		{
			pids[i] = fork();
			if (pids[i] < 0)
				perror("fork");
			else if (pids[i] == 0)
				ft_child(i, fds, cmd, data);
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
		waitpid(pids[j], &data->return_value, 0);
			// ver quando só tem um comando
		if (WIFEXITED(data->return_value))
			data->return_value = WEXITSTATUS(data->return_value);
		j++;
	}
	// Liberta memória
	free_pipes(fds, data->cmd_count - 1);
	free(pids);
}

