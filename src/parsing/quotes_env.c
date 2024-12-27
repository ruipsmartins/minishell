/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:47:59 by addicted          #+#    #+#             */
/*   Updated: 2024/12/27 12:39:18 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Função auxiliar para alocar memória para a string resultante
static char *allocate_result(size_t len)
{
	char *result = (char *)calloc(len + 2, sizeof(char)); // Trocar para ft_calloc, se necessário
	if (result == NULL)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	return result;
}

// Função para obter o valor da variável de ambiente
static const char *get_envvar_value(const char *start, const char *end, t_envvar *env_list)
{
	char *var_name;
	const char *value;
	
	var_name = strndup(start, end - start); // Trocar para ft_strndup, se necessário
	if(find_envvar(env_list, var_name))
		value = find_envvar(env_list, var_name)->value;
	else
		value = "";
	free(var_name);
	return value;
}

// Função para processar variáveis de ambiente
static void  process_envvar(const char **src, char **dst, t_data *data)
{
	t_envvar *env_list = data->env_var_lst;
	const char *start = ++(*src);
	const char *value;
	if (*(*src) == '?')
	{
		value = ft_itoa(data->return_value);
		(*src)++;
				
	}
	else
	{
		while (**src && (isalnum(**src) || **src == '_')) // Trocar para ft_isalnum, se necessário
			(*src)++;
		value = get_envvar_value(start, *src, env_list);
	}
	// if (value == )
	// {
	// 	printf("1Variable not found\n");
	// 	exit(EXIT_FAILURE);
	// 	free((char *)value);
	// }
	strcpy(*dst, value);   // Trocar para ft_strcpy, se necessário
	*dst += strlen(value); // Trocar para ft_strlen, se necessário
//	free((char *)value);
}

static void replace_vars(const char *input, char *result, t_data *data)
{
	const char *src = input;  // Ponteiro para ler a entrada
	char *dst = result;       // Ponteiro para escrever no resultado
	int in_double_quotes = 0; // Flag para indicar se estamos dentro de aspas duplas
	int in_single_quotes = 0; // Flag para indicar se estamos dentro de aspas simples

	while (*src)
	{
		if (*src == '\"') // Alternar estado de aspas duplas
		{
			in_double_quotes = !in_double_quotes;
			*dst++ = *src++; // Copiar aspas duplas para a saída
		}
		else if (*src == '\'' && !in_double_quotes) // Aspas simples fora de aspas duplas
		{
			in_single_quotes = !in_single_quotes;
			*dst++ = *src++; // Copiar aspas simples para a saída
		}
		else if (*src == '\'' && in_double_quotes) // Aspas simples dentro de aspas duplas
			*dst++ = *src++; // Copiar aspas simples para a saída sem alternar o estado
		else if (*src == '$' && (!in_single_quotes || in_double_quotes)) // Substituir variáveis
			process_envvar(&src, &dst, data);
		else
			*dst++ = *src++; // Copiar outros caracteres
	}
	*dst = '\0'; // Finalizar a string
}

// Função principal
char *replace_envvar(const char *input, t_data *data)
{
	char *result;

	size_t len = calculate_final_len(input, data);
	if (len == 0)
	{
		ft_printf("Error calculating final length\n");
		return NULL;
	}
	result = allocate_result(len);
	replace_vars(input, result, data);
	return result;
}
