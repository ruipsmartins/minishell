/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:01:43 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/18 20:33:59 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	read_lines_and_write(int write_fd, t_heredoc *tmp)
{
	char		*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, tmp->delimiter,
				ft_strlen(tmp->delimiter) + 1) == 0)
		{
			if (!line)
				print_error(HD_PRINT, NULL, 0);
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
	int			heredoc_fd;
	t_heredoc	*tmp;

	tmp = cmd->heredoc;
	heredoc_fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
	{
		perror("open .heredoc");
		return (-1);
	}
	if (read_lines_and_write(heredoc_fd, tmp) == -1)
	{
		close(heredoc_fd);
		return (-1);
	}
	close(heredoc_fd);
	return (0);
}
