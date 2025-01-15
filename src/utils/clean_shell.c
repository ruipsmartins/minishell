/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:16:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/15 19:15:45 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	close(0);
	close(1);
	close(2);
}

void	cleanup_child_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	if (data->executable != NULL)
		free(data->executable);
	if (data->cmd)
		free_command_list(data->cmd);
	free_pipes(data->fds, data->cmd_count - 1);
	free_env_list(data->env_var_lst);
	if (data->pids)
		free(data->pids);
	if (data->original_stdin != -1)
		close(data->original_stdin);
	if (data->original_stdout != -1)
		close(data->original_stdout);
	close(0);
	close(1);
	close(2);
}
