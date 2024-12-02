/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:23:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/02 12:04:06 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_flag(const char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 1;
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

void	echo_command(t_command *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (cmd->args[i] && validate_flag(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}
