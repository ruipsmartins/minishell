/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/10 15:56:26 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

int	count_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	close_all_pipes(int **fds, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

void	free_pipes(int **fds, int pipe_count)
{
	int	i;

	if (!fds)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (fds[i])
			free(fds[i]);
		i++;
	}
	free(fds);
}

void	close_all_parent_pipes(t_data *data, int i)
{
	if (i > 0)
	{
		close(data->fds[i - 1][0]);
		close(data->fds[i - 1][1]);
	}
}
