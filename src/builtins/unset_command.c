/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:24:23 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/07 15:14:16 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

//função para remover uma variável de ambiente da lista e modificar na data->env
void	unset_command(char *arg, t_data *data)
{
	t_envvar	*current;
	t_envvar	*previous;
	char		*name;

	name = ft_strdup(arg);
	current = data->env_var_lst;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
		{
			if (previous == NULL)
				data->env_var_lst = current->next;
			else
				previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			break;
		}
		previous = current;
		current = current->next;
	}
	data->env = swap_list_to_array(data->env_var_lst);
	free(name);
}


