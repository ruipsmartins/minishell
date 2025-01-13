/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:01:43 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/13 15:59:55 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_signal_and_pipe(int pipe_fd[2])
{
	signal(SIGINT, handle_here_doc_exit);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

static int	read_lines_and_write(t_command *cmd, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->heredoc->delimiter, 
				ft_strlen(cmd->heredoc->delimiter) + 1) == 0)
		{
			free(line);
			if(cmd->heredoc->next)
			{
				cmd->heredoc = cmd->heredoc->next;
				continue ;
			}
			else
				break ;
		}
		if(!cmd->heredoc->next)
		{
			write(write_fd, line, ft_strlen(line));
			write(write_fd, "\n", 1);
			free(line);
		}
	}
	if (g_var == 2)
	{
		close(write_fd);
		return (-1);
	}
	return (0);
}

int	execute_heredoc(t_command *cmd)
{
	int	pipe_fd[2];

	if (handle_signal_and_pipe(pipe_fd) == -1)
		return (-1);
	if (read_lines_and_write(cmd, pipe_fd[1]) == -1)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
