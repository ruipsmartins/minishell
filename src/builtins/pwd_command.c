/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:21:15 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/14 15:16:15 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para executar o comando pwd.
int	pwd_command(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = get_envvar(data->env_var_lst, "PWD");
		if (!cwd)
		{
			ft_putstr_fd("pwd: No such file or directory \n", STDERR_FILENO);
			return (data->return_value = 1);
		}
	}
	ft_printf("%s\n", cwd);
	if (cwd != get_envvar(data->env_var_lst, "PWD"))
		free(cwd);
	return (data->return_value = 0);
}
