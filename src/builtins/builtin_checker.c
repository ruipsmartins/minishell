/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:17:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/21 18:50:45 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin_checker(t_command *cmd, t_data *data)
{

	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		exit_command(data);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		pwd_command();
	else if (ft_strncmp(cmd->args[0], "cd", 4) == 0)
		cd_command(*cmd);
	else
		return false;

	return true;
}