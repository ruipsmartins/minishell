/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:01:43 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/16 13:31:26 by ruidos-s         ###   ########.fr       */
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

static int	write_line_to_fd(char *line, int write_fd)
{
	if (line)
	{
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	check_g_var(int write_fd)
{
	if (g_var == 2)
	{
		close(write_fd);
		return (-1);
	}
	return (0);
}

static int	read_lines_and_write(t_command *cmd, int write_fd)
{
	char		*line;
	t_heredoc	*tmp;

	tmp = cmd->heredoc;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, tmp->delimiter,
				ft_strlen(tmp->delimiter) + 1) == 0)
		{
			free(line);
			if (tmp->next)
			{
				tmp = tmp->next;
				continue ;
			}
			else
				break ;
		}
		if (!tmp->next)
			write_line_to_fd(line, write_fd);
	}
	if (check_g_var(write_fd) == -1)
		return (-1);
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
