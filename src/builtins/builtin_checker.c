/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:17:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/12 14:00:02 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin_execute(t_command *cmd, t_data *data)
{
	if (!cmd->args)
		return (false);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_command(cmd, data);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_command(data);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_command(*cmd, data);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_command(cmd, data);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_command(data);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_command(cmd, data);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_command(cmd, data);
	else
		return (false);
	return (true);
}

bool	builtin_checker(t_command *cmd)
{
	if (cmd->args == NULL)
		return (false);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (true);
	else if ((ft_strncmp(cmd->args[0], "export", 7) == 0)
		&& cmd->args[1] != NULL)
		return (true);
	else
		return (false);
	return (true);
}
