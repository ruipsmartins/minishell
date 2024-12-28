/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:14:53 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/28 10:22:58 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// printa a lista de variáveis de ambiente com export
void	print_exported_vars(t_envvar *env_var_lst)
{
	t_envvar	*current;

	current = env_var_lst;
	while (current != NULL)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
}

int	is_valid_identifier(const char *arg, t_data *data)
{
	if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		data->return_value = 1;
		return (0);
	}
	return (1);
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
		if (!is_valid_identifier(cmd->args[i], data))
		{
			i++;
			continue ;
		}
		process_env_variable(cmd->args[i], data);
		i++;
	}
}
