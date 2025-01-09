/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/09 14:25:53 by ruidos-s         ###   ########.fr       */
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
	//pid_t	pid;
	int		status;

	status = 0;
	/* pid = fork();
	if (pid < 0)
		write(STDERR_FILENO, "fork error\n", 11); */
	/* else if (pid == 0)
	{ */
	if (execve(executable, args, data->env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	//exit(EXIT_SUCCESS);
	//}
	/* else
	{
		cleanup_child_data(data);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		data->return_value = status;
	} */
	return (status);
}

void	execute_command_or_path(t_command *cmd, t_data *data)
{
	int		file_check;

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
		//ft_printf("cmd->args[0]= %s\n", cmd->args[0]);
		data->executable = find_executable(cmd->args[0], data);
		//ft_printf("data->executable: %s\n",data->executable);
		if (data->executable)
			execute_command(data->executable, cmd->args, data);
		else
			print_command_error(data, cmd->args[0], 127);
	}
}

void	execute(t_command *cmd, t_data *data)
{
	data->cmd = cmd;
	execute_piped_commands(cmd, data);
	if (data->return_value == 130 && !data->close_shell)
		write(2, "\n", 1);
	if (data->return_value == 131 && !data->close_shell)
		write(2, "Quit (core dumped)\n", 19);
}
