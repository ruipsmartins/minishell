/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/01 15:41:39 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "minishell.h"


void handle_fd(int in_fd, t_command * cmd, int  fd[2])
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

// No processo filho
void ft_child(int in_fd, t_command *cmd, int  fd[2], char **env)
{
    char *executable;

	handle_fd(in_fd, cmd, fd);
	// Encontrar o caminho completo do executável
	executable = find_executable(cmd->args[0]);
	if (!executable)
	{
		ft_printf("%s: Command not found\n", cmd->args[0]);
		exit(EXIT_FAILURE);
	}
	// Tratar redirecionamentos se necessário
	if (handle_redirects(cmd, NULL, NULL) == -1)
		exit(EXIT_FAILURE);
	// Executar o comando
	execute_command(executable, cmd->args, env);
	//perror("execve error");
	free(executable);
	exit(EXIT_FAILURE);
}

void execute_piped_commands(t_command *cmd, char **env)
{
    int fd[2];
    pid_t pid;
    int in_fd = 0;

    while (cmd != NULL)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            ft_child(in_fd, cmd, fd, env);
        }
        else if (pid < 0)
        {
            perror("fork error:");
            exit(EXIT_FAILURE);
        }
        else
        {
            // No processo pai
            wait(NULL);
            close(fd[1]);
            in_fd = fd[0];
            cmd = cmd->next;
        }
    }
}

/* char	***split_by_pipe(char *input)
{
	char	**pipe_segments = malloc(64 * sizeof(char *));
	char	***commands = malloc(64 * sizeof(char **));
	char	*segment;
	int		i = 0;
	int		j = 0;

	segment = ft_strtok(input, "|");
	while (segment)
	{
		pipe_segments[i++] = segment;
		segment = ft_strtok(NULL, "|");
	}
	pipe_segments[i] = NULL;
	while (pipe_segments[j])
	{
		commands[j] = parse_command(pipe_segments[j]);
		j++;
	}
	commands[i] = NULL;
	free(pipe_segments);
	return (commands);
}
 */