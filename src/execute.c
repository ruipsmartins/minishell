/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/02 17:46:29 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "minishell.h"

//Função para encontrar executavel no path
char	*find_executable(const char *command)
{
	char	*path;
	char	*dir;
	char	*full_path;
	char	*path_copy;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(ft_strlen(dir) + ft_strlen(command) + 2);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, dir, ft_strlen(dir) + 1);
		ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
		ft_strlcat(full_path, command,
			ft_strlen(full_path) + ft_strlen(command) + 1);
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
        // Processo filho
		//handle_redirections(args);
		if (execve(command, args, env) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
        // Processo pai
		waitpid(pid, &status, 0);
	}
}


void execute_command_or_path(t_command *cmd, char **env)
{
    char *executable;

    // Verifica se o comando é um caminho absoluto ou relativo
    if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.') {
        if (access(cmd->args[0], X_OK) == 0)
            execute_command(cmd->args[0], cmd->args, env);
        else
            ft_printf("%s: No such file or directory\n", cmd->args[0]);
    } else {
        // Tenta encontrar o executável no PATH
        executable = find_executable(cmd->args[0]);
        if (executable) {
            execute_command(executable, cmd->args, env);
            free(executable);
        } else
            ft_printf("%s: Command not found\n", cmd->args[0]);
    }
}

void	execute(t_command *cmd, char **env)
{
        execute_piped_commands(cmd, env);
}


