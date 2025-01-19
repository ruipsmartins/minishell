/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/19 11:27:34 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para encontrar o executável no path
char	*find_executable(const char *command, t_data *data)
{
	char	*path;
	char	*dir;
	char	*full_path;

	if (!command[0])
		return (NULL);
	path = get_path_value(data);
	if (!path)
		return (NULL);
	dir = ft_strtok(path, ":");
	while (dir != NULL)
	{
		full_path = get_executable_path(command, dir);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

// Função para executar o comando
int	execute_command(char *executable, char **args, t_data *data)
{
	unlink(".heredoc");
	if (execve(executable, args, data->env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	execute_command_or_path(t_command *cmd, t_data *data)
{
	int	file_check;

	if (cmd->heredoc)
		dup2(open(".heredoc", O_RDONLY), STDIN_FILENO);
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		file_check = check_file_type(cmd->args[0]);
		if (file_check == 0)
			execute_command(cmd->args[0], cmd->args, data);
		else if (file_check == 126)
			print_command_error(data, cmd->args[0], 126);
		else
			print_command_error(data, cmd->args[0], 127);
	}
	else
	{
		data->executable = find_executable(cmd->args[0], data);
		if (data->executable)
			execute_command(data->executable, cmd->args, data);
		else
			print_command_error(data, cmd->args[0], 127);
	}
}

void	execute_all_heredocs(t_command *cmd, t_data *data)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		if (current->heredoc)
		{
			if (execute_heredoc(current) == -1) // Executa o heredoc e verifica erros
			{
				data->return_value = 1; // Define o código de retorno em caso de erro
				return;
			}
		}
		current = current->next; // Avança para o próximo comando na lista
	}
}

void	execute(t_command *cmd, t_data *data)
{
	data->cmd = cmd;
	execute_all_heredocs(cmd, data);
	execute_piped_commands(cmd, data);
	if (data->return_value == 130 && !data->close_shell)
		write(2, "\n", 1);
	if (data->return_value == 131 && !data->close_shell)
		write(2, "Quit (core dumped)\n", 19);
}
