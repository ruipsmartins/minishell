/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:23:16 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/16 13:04:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**swap_list_to_array_rui(t_envvar *env_list)
{
    t_envvar *current;
    int i;
    char **env;
    char *temp;

    i = 0;
    current = env_list;
    while(current != NULL)
    {
        current = current->next;
        i++;
    }
    current = env_list;
    env = (char **)malloc((i + 1) * sizeof(char *));
    i = 0;
    while (current != NULL)
    {
        temp = ft_strjoin(current->name, "=");
        env[i] = ft_strjoin(temp, current->value);
        free(temp); // Free the temporary string
        current = current->next;
        i++;
    }
    env[i] = NULL;
    return (env);
}

char *get_envvar(t_envvar *env_list, const char *name)
{
	t_envvar *current;

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
    int i;

    // Atualiza data->env com a nova lista de variáveis de ambiente
    if (data->env != NULL)
    {
        // Libera a memória previamente alocada para data->env
        i = 0;
        while (data->env[i] != NULL)
        {
            free(data->env[i]);
            i++;
        }
        free(data->env);
    }
    data->env = swap_list_to_array_rui(data->env_var_lst);
    // Imprime as variáveis de ambiente
    i = 0;
    while (data->env[i])
    {
        ft_printf("%s\n", data->env[i]);
        i++;
    }
    data->return_value = 0;
}
