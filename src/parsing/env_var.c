/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2024/12/30 11:30:27 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Adiciona uma nova variável de ambiente à lista de variaveis ou substitui
// o valor de uma variável de ambiente existente
void	set_envvar(t_envvar *envvar_list, char *name, char *value)
{
	t_envvar	*current;

	current = find_envvar(envvar_list, name);
	if (current != NULL)
	{
		free(current->value);
		current->value = strdup(value);
		return ;
	}
	else
		ft_new_envvar(&envvar_list, name, value);
	return ;
}

char	*find_envvar_value(t_envvar *env_var_lst, char *var_name)
{
	t_envvar	*env;

	env = find_envvar(env_var_lst, var_name);
	if (env)
		return (env->value);
	return (NULL);
}

char	*extract_var_name(const char **src)
{
	const char	*start;

	start = *src;
	while (**src && (ft_isalnum(**src) || **src == '_'))
		(*src)++;
	if (*src == start)
		return (NULL);
	return (strndup(start, *src - start));
}

size_t	handle_variable(const char **src, t_data *data)
{
	size_t	len;
	char	*var_name;
	char	*value;

	len = 0;
	(*src)++;
	if (**src == '?')
	{
		len += size_return(data->return_value);
		return (len);
	}
	var_name = extract_var_name(src);
	if (var_name)
	{
		value = find_envvar_value(data->env_var_lst, var_name);
		if (value)
			len += ft_strlen(value);
		if (!value)
			len += ft_strlen(var_name);
		free(var_name);
	}
	return (len);
}
