/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:49:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/26 11:53:03 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL)
	{
		perror("cd");
		return ;
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return ;
	}
}

void	cd_command(t_command cmd)
{
	int	i;

	i = 0;
	while (cmd.args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	else if (cmd.args[1] == NULL || (cmd.args[1][0] == '~'
		&& cmd.args[1][1] == '\0'))
	{
		cd_home();
	}
	else
	{
		if (chdir(cmd.args[1]) == -1)
		{
			perror("cd");
			return ;
		}
	}
}

