/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:14:53 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/17 13:11:45 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// printa a lista de variáveis de ambiente com export
void	print_exported_vars(t_envvar *env_var_lst)
{
	t_envvar	*current;
	int			i;

	current = env_var_lst;
	while (current != NULL)
	{
		if (current->value)
		{
			ft_printf("declare -x %s=\"", current->name);
			i = 0;
			while (current->value[i])
			{
				if (current->value[i] == '\\' || current->value[i] == '\"'
					|| current->value[i] == '$')
					ft_printf("\\");
				ft_printf("%c", current->value[i]);
				i++;
			}
			ft_printf("\"\n");
		}
		else
			ft_printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

int	is_valid_identifier(char *arg, t_data *data)
{
	int	i;

	if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
		return (data->return_value = 1);
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]))
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
			return (data->return_value = 1);
		}
		i++;
	}
	return (0);
}

void	update_or_create_env_variable(char *name, char *value, t_data *data)
{
	t_envvar	*current;

	current = find_envvar(data->env_var_lst, name);
	if (current != NULL)
	{
		free(current->value);
		if (value != NULL)
			current->value = ft_strdup(value);
		else
			current->value = NULL;
	}
	else
	{
		ft_new_envvar(&data->env_var_lst, name, value);
	}
}

void	process_env_variable(const char *arg, t_data *data)
{
	char	*env_var;
	char	*equal_sign;
	char	*name;
	char	*value;

	env_var = ft_strdup(arg);
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign != NULL)
	{
		name = ft_substr(env_var, 0, equal_sign - env_var);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		name = ft_strdup(env_var);
		value = NULL;
	}
	update_or_create_env_variable(name, value, data);
	free(env_var);
	free(name);
	if (value)
		free(value);
}

// função para adicionar ou modificar uma variável de ambiente
void	export_command(t_command *cmd, t_data *data)
{
	int	i;

	data->return_value = 0;
	if (cmd->args[1] == NULL)
	{
		print_exported_vars(data->env_var_lst);
		return ;
	}
	if (ft_strncmp(cmd->args[1], "_=", 2) == 0)
		return ;
	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_identifier(cmd->args[i], data))
		{
			i++;
			continue ;
		}
		process_env_variable(cmd->args[i], data);
		i++;
	}
}
