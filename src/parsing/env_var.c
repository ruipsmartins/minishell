/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2024/12/02 11:49:56 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// Adiciona uma nova variável de ambiente à lista de variaveis ou substitui o valor de uma variável de ambiente existente
void set_envvar(t_envvar *envvar_list, char *name, char *value)
{
	t_envvar *current;

	current = find_envvar(envvar_list, name);
	if(current != NULL)
	{
		free(current->value);
		current->value = strdup(value);
		return;
	}
	else
		ft_new_envvar(&envvar_list, name, value);
	return;
}

// PRINTA A LISTA DE VARIAVEIS DE AMBIENTE
void print_list_envvar(t_envvar *env_list)
{
	t_envvar *current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

size_t calculate_final_len(const char *input, t_envvar *env_list)
{
	size_t len;
	const char *src;
	const char *start;
	char *var_name;
	
	len = 0;
	src = input;
	while(*src)
	{
		if(*src == '$')
		{
			if(*(src + 1) == '?')
			{
				printf("not done yet\n");
				return(0);
			}
			else
			{
				start = ++src;
			while(*src && (isalnum(*src) || *src == '_')) // passar para ft_isalnum
				src++;
			var_name = strndup(start, src - start); // passar para ft_strndup
			if (find_envvar(env_list, var_name) == NULL)
			{
				printf("%s not found\n", var_name);
				return (0);
			}
			len += strlen((find_envvar(env_list, var_name)->value));
			free(var_name);
			// if (get_envvar(env_list, var_name) == NULL)
			// {
			// 	printf("%s not found\n", var_name);
			// 	return (0);
			// }
			// len += strlen(get_envvar(env_list, var_name));
			// free(var_name);
			}
		}
		else
		{
			len++;
			src++;
		}
	}
	return len;
}

/*
// Substitui as variáveis de ambiente na lista de variáveis
char	*replace_envvar(const char *input, t_envvar *env_list)
{
	char		*result;
	size_t		len;
	const char *src;
	char 		*dst;

	const char *start; // para guardar o inicio da variavel
	char		*var_name; // para guardar o nome da variavel
	const char *value; // para guardar o valor da variavel
	
	len = 0;
	src = input;
	len = calculate_final_len(input, env_list);
	if(len == 0)
	{
		printf("Error calculating final len\n");
		return (NULL);
	}
	//alocar memoria para a string final
	result = (char *)calloc(len + 2, sizeof(char)); // calloc tem de passar para ft_calloc
	if (result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	//Trocar variaveis ambientes
	src = input;
	dst = result;
	
	while(*src)
	{
		if(*src == '$')
		{
			if(*(src + 1) == '?')
			{
				printf("AINDA NAO FEITO\n");
				return (0);
			}
			else
			{
				start = ++src;
				while (*src && (isalnum(*src) || *src == '_')) // passar para ft_isalnum
					src++;
				var_name = strndup(start, src - start); // passar para ft_strndup
				value = find_envvar(env_list, var_name)->value;
				//printf("var_name: %s...\nstart: %s...\nsrc: %s...\n", var_name, start, src);
				if (value == NULL)
				{
					printf("%s not found\n", var_name);
					return (0);
				}
				strcpy(dst, value); //passar para ft_strcpy
				dst += strlen(value); // passar para ft_strlen
				free(var_name);
			}
		}
		else
			*dst++ = *src++;
	}
	*dst = '\0';
	return (result);
}
*/

void free_env_list(t_envvar *env_list)
{
	t_envvar *current;
	t_envvar *next;

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
