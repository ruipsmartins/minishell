/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/19 12:11:21 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"
#include <sys/stat.h>

// Função para obter o caminho do executável
char	*get_executable_path(const char *command, const char *dir)
{
	char	*full_path;
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(command);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, dir_len + 1);
	ft_strlcat(full_path, "/", dir_len + 2);
	ft_strlcat(full_path, command, dir_len + cmd_len + 2);
	return (full_path);
}

char	*get_path_value(t_data *data)
{
	t_envvar	*path_var;

	path_var = find_envvar(data->env_var_lst, "PATH");
	if (!path_var)
	{
		return (NULL);
	}
	return (ft_strdup(path_var->value));
}

// Função para encontrar o executável no path
char	*find_executable(const char *command, t_data *data)
{
	char	*path;
	char	*dir;
	char	*full_path;

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
int	execute_command(char *command, char **args, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		write(STDERR_FILENO, "fork error\n", 11);
	else if (pid == 0)
	{
		if (execve(command, args, data->env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		data->return_value = status;
	}
	return (status);
}

void	execute_command_or_path(t_command *cmd, t_data *data)
{
	char	*executable;
	int		file_check;

	if(!cmd->args)
	{
		data->return_value=0;
		return ;
	}
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
		executable = find_executable(cmd->args[0], data);
		if (executable)
		{
			execute_command(executable, cmd->args, data);
			free(executable);
		}
		else
			print_command_error(data, cmd->args[0], 127);
	}
}

void	execute(t_command *cmd, t_data *data)
{
	data->cmd = cmd;
	execute_piped_commands(cmd, data);
	//ft_printf("return value: %d\n", data->return_value);
}
