/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:49:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/17 23:18:09 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cd_home(t_data *data)
{
	char	*home;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	home = get_envvar(data->env_var_lst, "HOME");
	if (home == NULL)
	{
		free(oldpwd);
		print_error("Minishell: cd: HOME not set\n", data, 1);
		return ;
	}
	else if (chdir(home) == -1)
	{
		free(oldpwd);
		data->return_value = 1;
		perror("chdir: ");
		return ;
	}
	else
	{
		set_envvar(data->env_var_lst, "OLDPWD", oldpwd);
		set_envvar(data->env_var_lst, "PWD", home);
		free(oldpwd);
	}
}

static void	cd_oldpwd(t_data *data)
{
	char	*oldpwd;
	char	*current_pwd;

	oldpwd = get_envvar(data->env_var_lst, "OLDPWD");
	if (oldpwd == NULL)
	{
		print_error("Minishell: cd: OLDPWD not set\n", data, 1);
		return ;
	}
	current_pwd = getcwd(NULL, 0);
	if (chdir(oldpwd) == -1)
	{
		perror("cd");
		data->return_value = 1;
		free(current_pwd);
		return ;
	}
	set_envvar(data->env_var_lst, "OLDPWD", current_pwd);
	free(current_pwd);
	current_pwd = getcwd(NULL, 0);
	set_envvar(data->env_var_lst, "PWD", current_pwd);
	free(current_pwd);
	data->return_value = 0;
}

void	change_directory(t_data *data, char *path)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_strdup(get_envvar(data->env_var_lst, "PWD"));
	if (chdir(path) == -1)
	{
		free(oldpwd);
		perror("cd");
		data->return_value = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		set_envvar(data->env_var_lst, "OLDPWD", oldpwd);
		set_envvar(data->env_var_lst, "PWD", pwd);
		free(oldpwd);
		free(pwd);
		data->return_value = 0;
	}
}

int	cd_command(t_command cmd, t_data *data)
{
	int	i;

	i = 0;
	data->return_value = 0;
	while (cmd.args[i])
		i++;
	if (i > 2)
	{
		return (print_error("cd: too many arguments\n", data, 1));
	}
	else if (cmd.args[1] == NULL || (cmd.args[1][0] == '~'
		&& cmd.args[1][1] == '\0'))
		cd_home(data);
	else if (cmd.args[1][0] == '-' && cmd.args[1][1] == '\0')
		cd_oldpwd(data);
	else
		change_directory(data, cmd.args[1]);
	return (data->return_value);
}
