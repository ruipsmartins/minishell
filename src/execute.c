/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/06 09:33:35 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

//Função para encontrar executavel no path
char	*find_executable(const char *command)
{
	char	*path;
	char	*dir;
	char	full_path[1024];
	char	*path_copy;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		ft_strlcpy(full_path, dir, 1024);
		ft_strlcat(full_path, "/", 1024);
		ft_strlcat(full_path, command, 1024);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (ft_strdup(full_path));
		}
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
	if (pid == 0)
	{
        // Processo filho
		if (execve(command, args, env) == -1)
			write(STDERR_FILENO, "execve error\n", 13);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		write(STDERR_FILENO, "fork error\n", 11);
	}
	else
	{
        // Processo pai
		waitpid(pid, &status, 0);
	}
}

// Verificar se é um caminho absoluto, relativo ou só o nome do executável
void	execute_path(char *command, char **args, char **env)
{
	char	*executable;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			execute_command(command, args, env);
		else
			write(STDERR_FILENO, "Command not found\n", 18);
	}
	else
	{
		executable = find_executable(command);
		if (executable)
		{
			execute_command(executable, args, env);
			free(executable);
		}
		else
			write(STDERR_FILENO, "Command not found in PATH\n", 26);
	}
}
