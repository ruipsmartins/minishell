/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2024/12/18 14:01:45 by duamarqu         ###   ########.fr       */
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

// PRINTA A LISTA DE VARIAVEIS DE AMBIENTE
void	print_list_envvar(t_envvar *env_list)
{
	t_envvar	*current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

int	size_return(int return_value)
{
	int	size_of_nbm;

	size_of_nbm = 1;
	while (return_value / 10)
	{
		return_value /= 10;
		size_of_nbm++;
	}
	return (size_of_nbm);
}

// size_t	calculate_final_len(const char *input, t_data *data)
// {
// 	size_t len;
// 	const char *src;
// 	const char *start;
// 	char *var_name;

// 	len = 0;
// 	src = input;
// 	while(*src)
// 	{
// 		if(*src == '$')
// 		{
// 			if(*(src + 1) == '?')
// 				len += size_return(data->return_value);
// 				start = ++src;
// 			while(*src && (isalnum(*src) || *src == '_')) // passar para ft_isalnum
// 				src++;
// 			var_name = strndup(start, src - start); // passar para ft_strndup
// 			if (find_envvar(data->env_var_lst, var_name))
// 				len += strlen((find_envvar(data->env_var_lst, var_name)->value));
// 			free(var_name);
// 		}
// 		else
// 		{
// 			len++;
// 			src++;
// 		}
// 	}
// 	return len;
// }
char	*find_envvar_value(t_envvar *env_var_lst, const char *var_name)
{
	t_envvar *env;
	
	env = find_envvar(env_var_lst, var_name);
	if (env)
		return env->value;

	return NULL;
}

char	*extract_var_name(const char **src)
{
	const char *start;

	start = *src;
	while (**src && (ft_isalnum(**src) || **src == '_'))
		(*src)++;

	if (*src == start) // Nenhum caractere válido foi encontrado
		return NULL;

	return strndup(start, *src - start);
}

size_t	handle_variable(const char **src, t_data *data)
{
	size_t len;
	char *var_name;
	char *value;

	len = 0;
	(*src)++; // Avança após o '$'
	if (**src == '?')
	{
		len += size_return(data->return_value);
		(*src)++;
		return len;
	}
	var_name = extract_var_name(src);
	if (var_name)
	{
		char *value = find_envvar_value(data->env_var_lst, var_name);
		if (value)
			len += strlen(value);
		free(var_name);
	}
	return len;
}


size_t	calculate_final_len(const char *input, t_data *data)
{
	size_t	len;
	const char *src;

	len = 0;
	src = input;
	while (*src)
	{
		if (*src == '$')
		{
			len += handle_variable(&src, data);
		}
		else
		{
			len++;
			src++;
		}
	}
	return len;
}


void	free_env_list(t_envvar *env_list)
{
	t_envvar	*current;
	t_envvar	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}
