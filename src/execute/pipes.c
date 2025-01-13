/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/10 17:26:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

// Função para executar o comando no processo filho.
void	execute_child_process(int i, int **fds, t_command *cmd, t_data *data)
{
	if (i > 0)
		dup2(fds[i - 1][0], STDIN_FILENO);
	if (cmd->next != NULL)
		dup2(fds[i][1], STDOUT_FILENO);
	close_all_pipes(fds, data->cmd_count - 1);
	if (handle_redirects(cmd, data) == -1)
		exit(data->return_value);
	if (!cmd->args || !cmd->args[0])
	{
		cleanup_child_data(data);
		exit(data->return_value);
	}
	if (builtin_execute(cmd, data))
	{
		cleanup_child_data(data);
		exit(data->return_value);
	}
	execute_command_or_path(cmd, data);
	if (g_var == 2)
		data->return_value = 130;
	exit(data->return_value);
}

/* Inicializa os pipes e os PIDs para o pipeline. */
void	init_pipes_and_pids(t_data *data, int cmd_count)
{
	int	i;

	data->fds = malloc(sizeof(int *) * (cmd_count - 1));
	data->pids = malloc(sizeof(pid_t) * cmd_count);
	i = 0;
	while (i < data->cmd_count - 1)
	{
		data->fds[i] = malloc(sizeof(int) * 2);
		if (pipe(data->fds[i]) < 0)
			perror("pipe");
		data->pids[i] = 0;
		i++;
	}
}
// Função para esperar pelos processos filhos.
void	wait_for_children(t_data *data, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count)
	{
		if (data->pids && data->pids[j] > 0)
		{
			waitpid(data->pids[j], &data->return_value, 0);
			if (WIFEXITED(data->return_value))
				data->return_value = WEXITSTATUS(data->return_value);
		}
		j++;
	}
}
// Função para executar um único comando.
void	run_single_command(t_command *cmd, t_data *data, int index)
{
	if (should_execute_in_parent(cmd))
	{
		if (data->cmd_count == 1)
			builtin_execute(cmd, data);
		data->pids[index] = -1;
	}
	else
	{
		data->pids[index] = fork();
		if (data->pids[index] < 0)
			perror("fork");
		else if (data->pids[index] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			execute_child_process(index, data->fds, cmd, data);
		}
		else
			signal(SIGINT, ctrl_c_child);

	}
}

/* Função para executar comandos em sequência,
utilizando pipes para a comunicação entre processos. */
void	execute_piped_commands(t_command *cmd, t_data *data)
{
	int	i;

	data->cmd_count = count_commands(cmd);
	init_pipes_and_pids(data, data->cmd_count);
	i = 0;
	while (cmd != NULL)
	{
		run_single_command(cmd, data, i);
		close_all_parent_pipes(data, i);
		cmd = cmd->next;
		i++;
	}
	close_all_pipes(data->fds, data->cmd_count - 1);
	wait_for_children(data, data->cmd_count);
	free_pipes(data->fds, data->cmd_count - 1);
	free(data->pids);
	signal(SIGINT, ctrl_c_parent);
}
