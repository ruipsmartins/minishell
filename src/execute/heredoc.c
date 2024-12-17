/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:01:43 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/16 15:23:34 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_heredoc(t_command *cmd)
{
	int		pipe_fd[2];
	char	*line;

	signal(SIGINT, handle_here_doc_exit);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->delimiter,
				ft_strlen(cmd->delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	if (global_var == 130)
	{
		//ft_printf("heredoc terminado por ctl+c\n");
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		return (-1);\
	}
	//ft_printf("heredoc terminado normalmente\n");
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
