/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:16:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/18 12:06:19 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void cleanup_data(t_data *data)
{
	int i;

	i = 0;
	while(data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	//if(data->cmd)
		//free_command_list(data->cmd);
}


void cleanup_child_data(t_data *data)
{
	int i;

	i = 0;
	while(data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	if(data->cmd)
		free_command_list(data->cmd);
	free_pipes(data->fds, data->cmd_count - 1);
	if (data->pids)
		free(data->pids);
}

