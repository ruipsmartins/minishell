/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:17:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/17 15:56:42 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin_checker_parent(t_command *cmd, t_data *data)
{
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_command(cmd, data);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_command(data);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		cd_command(*cmd, data);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		echo_command(cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		env_command(data);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		export_command(cmd->args[1], data);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		unset_command(cmd->args[1], data);
	else
		return (false);
	return (true);
}

bool	builtin_checker_child(t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (true);
	else
		return (false);
	return (true);
}
