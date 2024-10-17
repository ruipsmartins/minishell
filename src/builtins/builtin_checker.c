/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:17:35 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/17 15:54:24 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	builtin_checker(t_command *cmd)
{

	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
	{
		exit_command();
		return true;
	}

	return false;
}