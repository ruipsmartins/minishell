/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:17:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/17 11:27:02 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para executar os builtins.
bool	builtin_execute(t_command *cmd, t_data *data)
{
	signal(SIGPIPE, SIG_IGN);
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
	{
		signal(SIGPIPE, SIG_DFL);
		return (false);
	}
	return (true);
}

/* Função para verificar se o comando deve ser executado no processo pai. */
bool	should_execute_in_parent(t_command *cmd)
{
	if (cmd->args == NULL)
		return (false);
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
