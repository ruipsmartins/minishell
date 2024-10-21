/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/21 18:48:27 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

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

// Função para encontrar o executável no path
char	*find_executable(const char *command)
{
	char	*path;
	char	*dir;
	char	*path_copy;
	char	*full_path;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = get_executable_path(command, dir);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

// Função para executar o comando
void	execute_command(char *command, char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		write(STDERR_FILENO, "fork error\n", 11);
	else if (pid == 0)
	{
		if (execve(command, args, env) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	execute_command_or_path(t_command *cmd, t_data *data)
{
	char	*executable;

	if (builtin_checker(cmd, data) == false)
	{
		if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
		{
			if (access(cmd->args[0], X_OK) == 0)
				execute_command(cmd->args[0], cmd->args, data->env);
			else
				print_command_error(cmd->args[0], 2);
		}
		else
		{
			executable = find_executable(cmd->args[0]);
			if (executable)
			{
				execute_command(executable, cmd->args, data->env);
				free(executable);
			}
			else
				print_command_error(cmd->args[0], 1);
		}
	}
}

/* 	 t_command *current = cmd;
    int i = 0;
    while (current != NULL)
    {
        ft_printf("Comando %d:\n", i);
        ft_printf("  Args: ");
        int j = 0;
        while (current->args[j] != NULL)
        {
            ft_printf("%s ", current->args[j]);
            j++;
        }
        ft_printf("\n");
        ft_printf("  Input File: %s\n", current->input_file);
        ft_printf("  Output File: %s\n", current->output_file);
        ft_printf("\n");
        current = current->next;
        i++;
    } */
void	execute(t_command *cmd, char **env)
{
	t_data	data;

	data.cmd = cmd;
	data.env = env;
	data.original_stdin = -1;
	data.original_stdout = -1;
	data.close_shell = false;
	execute_piped_commands(cmd, &data);
}
