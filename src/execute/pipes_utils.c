/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:05:58 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/16 13:12:14 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "minishell.h"

bool	should_execute_in_parent(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0 || ft_strncmp(cmd->args[0],
			"unset", 6) == 0 || ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (true);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
	{
		if (cmd->args[1] != NULL)
			return (true);
		return (false);
	}
	return (false);
}

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

	if (!fds) // Verifica se fds é NULL
		return ;
	i = 0;
	while (i < pipe_count)
	{
		if (fds[i]) // Verifica se fds[i] foi alocado
			free(fds[i]);
		i++;
	}
	free(fds); // Liberta o array de ponteiros
}

void	close_all_parent_pipes(t_data *data, int i)
{
	if (i > 0)
	{
		close(data->fds[i - 1][0]);
		close(data->fds[i - 1][1]);
	}
}
