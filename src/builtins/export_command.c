/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:14:53 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/28 14:07:39 by ruidos-s         ###   ########.fr       */
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

// função para adicionar ou modificar uma variável de ambiente
void	export_command(t_command *cmd, t_data *data)
{
	char		*name;
	char		*value;
	char		*env_var;
	t_envvar	*current;
	int			i;
	char		*equal_sign;

	i = 1;
	if (cmd->args[1] == NULL)
	{
		print_exported_vars(data->env_var_lst);
		return ;
	}
	while (cmd->args[i])
	{
		// Verificar se é um identificador válido
		if (ft_isdigit(cmd->args[i][0]) || !ft_isalpha(cmd->args[i][0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				cmd->args[i]);
			data->return_value = 1;
			i++;
			continue ;
		}
		// Obter a variável completa
		env_var = ft_strdup(cmd->args[i]);
		equal_sign = ft_strchr(env_var, '=');
		if (equal_sign != NULL)
		{
			// Caso com '=' (b= ou c=coisas)
			name = ft_substr(env_var, 0, equal_sign - env_var);
			value = ft_strdup(equal_sign + 1); // Pode ser vazio
		}
		else
		{
			// Caso sem '=' (a)
			name = ft_strdup(env_var);
			value = NULL;
		}
		// Procurar na lista
		current = find_envvar(data->env_var_lst, name);
		if (current != NULL)
		{
			free(current->value);
			current->value = value ? ft_strdup(value) : NULL;
		}
		else
			ft_new_envvar(&data->env_var_lst, name, value);
		free(env_var);
		free(name);
		if (value)
			free(value);
		i++;
	}
}

