/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:23:16 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/02 12:10:29 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_valid_envvars(t_envvar *env_list)
{
	t_envvar	*current;
	int			count;

	count = 0;
	current = env_list;
	while (current != NULL)
	{
		if (current->value != NULL)
			count++;
		current = current->next;
	}
	return (count);
}

char	**swap_list_to_array(t_envvar *env_list)
{
	t_envvar	*current;
	char		**env;
	char		*temp;
	int			i;
	int			count;

	count = count_valid_envvars(env_list);
	env = (char **)malloc((count + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	current = env_list;
	i = 0;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			temp = ft_strjoin(current->name, "=");
			env[i] = ft_strjoin(temp, current->value);
			free(temp);
			i++;
		}
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}

char	*get_envvar(t_envvar *env_list, const char *name)
{
	t_envvar	*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	env_command(t_data *data)
{
	int	i;

	if (data->env != NULL)
	{
		i = 0;
		while (data->env[i] != NULL)
		{
			free(data->env[i]);
			i++;
		}
		free(data->env);
	}
	data->env = swap_list_to_array(data->env_var_lst);
	i = 0;
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	data->return_value = 0;
}
