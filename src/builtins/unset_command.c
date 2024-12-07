/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:24:23 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/28 15:03:36 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_var(t_envvar **env_var_lst, const char *name)
{
	t_envvar	*current;
	t_envvar	*previous;

	current = *env_var_lst;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
		{
			if (previous == NULL)
				*env_var_lst = current->next;
			else
				previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

// função para remover uma variável de ambiente da lista
void	unset_command(t_command *cmd, t_data *data)
{
	int		i;
	char	*name;

	i = 1;
	while (cmd->args[i])
	{
		name = ft_strdup(cmd->args[i]);
		remove_env_var(&data->env_var_lst, name);
		free(name);
		i++;
	}
}
