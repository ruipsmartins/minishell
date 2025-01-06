/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:47:59 by addicted          #+#    #+#             */
/*   Updated: 2025/01/06 12:32:53 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função auxiliar para alocar memória para a string resultante
static char	*allocate_result(size_t len)
{
	char	*result;

	result = (char *)ft_calloc(len + 2, sizeof(char));
	if (result == NULL)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	return (result);
}

// Função para obter o valor da variável de ambiente
const char	*get_envvar_value(const char *start, const char *end,
t_envvar *env_list)
{
	char		*var_name;
	const char	*value;

	var_name = ft_strndup(start, end - start);
	if (find_envvar(env_list, var_name))
		value = find_envvar(env_list, var_name)->value;
	else
		value = "";
	free(var_name);
	return (value);
}

// Função para processar variáveis de ambiente
void	process_envvar(const char **src, char **dst, t_data *data)
{
	t_envvar	*env_list;
	const char	*start;
	const char	*value;

	start = ++(*src);
	env_list = data->env_var_lst;
	if (*(*src) == '?')
	{
		value = ft_itoa(data->return_value);
		(*src)++;
		ft_strcpy(*dst, value);
		*dst += ft_strlen(value);
		free((char *)value);
	}
	else
	{
		while (**src && (isalnum(**src) || **src == '_'))
			(*src)++;
		value = get_envvar_value(start, *src, env_list);
		ft_strcpy(*dst, value);
		*dst += ft_strlen(value);
	}
}

// Função principal
char	*replace_envvar(const char *input, t_data *data)
{
	char	*result;
	size_t	len;

	len = calculate_final_len(input, data);
	if (len == 0)
	{
		ft_printf("Error calculating final length\n");
		return (NULL);
	}
	result = allocate_result(len);
	replace_vars(input, result, data);
	return (result);
}
