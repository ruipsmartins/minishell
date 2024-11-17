/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:15:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/17 17:13:58 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_numeric(const char *str)
{
	if ((*str == '-' || *str == '+') && ft_isdigit(*(str + 1)))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	exit_command(t_command *cmd, t_data *data)
{
	int	exit_status;

	ft_printf("EXIT\n");
	if (cmd->args[1] != NULL && !is_numeric(cmd->args[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n",
			cmd->args[1]);
		data->return_value = 2;
		data->close_shell = true;
		return ;
	}
	else if (cmd->args[1] != NULL && cmd->args[2] != NULL)
	{
		ft_printf("minishell: exit: too many arguments\n");
		data->return_value = 1;
		return ;
	}
	else if (cmd->args[1] != NULL)
	{
		exit_status = ft_atoi(cmd->args[1]);
		data->return_value = exit_status % 256;
	}
	data->close_shell = true;
}
