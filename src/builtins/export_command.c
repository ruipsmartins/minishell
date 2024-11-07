/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:14:53 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/07 14:14:55 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//função para adicionar ou modificar uma variável de ambiente
void	export_command(char *arg, t_data *data)
{
	char	*name;
	char	*value;
	char	*env_var;
	t_envvar *current;

	env_var = ft_strdup(arg);
	name = ft_strtok(env_var, "=");
	value = ft_strtok(NULL, "=");
	if (name == NULL)
	{
		free(env_var);
		return;
	}
	current = find_envvar(data->env_var_lst, name);
	if (current != NULL)
	{
		free(current->value);
		current->value = ft_strdup(value);
	}
	else
		ft_new_envvar(&data->env_var_lst, name, value);
	free(env_var);
}


