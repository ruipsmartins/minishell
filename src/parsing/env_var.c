/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2024/10/30 13:06:36 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void set_envvar(t_envvar *envvar_list, const char *name, const char *value)
{
	t_envvar *current;
	t_envvar *prev;
	t_envvar *new_var;

	current = envvar_list;
	prev = NULL;
	while (current != NULL) // verificar se a variavel exitste
	{
		printf("current->name: %s\n", current->name);
		if (strcmp(current->name, name) == 0) // strcmp tem de passar para ft_strcmp mas nao esta feito
		{
			free(current->value);
			current->value = strdup(value); // STRDUP TEM DE PASSAR PARA FT_STRDUP
			return;
		}
		prev = current;
		current = current->next;
	}
	new_var = (t_envvar *)calloc(1, sizeof(t_envvar)); // alocar memoria para a nova variavel // calloc tem de passar para ft_calloc
	new_var->name = strdup(name);                      // STRDUP TEM DE PASSAR PARA FT_STRDUP
	new_var->value = strdup(value);                    // STRDUP TEM DE PASSAR PARA FT_STRDUP
	new_var->next = NULL;
	if (prev == NULL)
		envvar_list = new_var;
	else
		prev->next = new_var;
}
char *get_envvar(t_envvar *env_list, const char *name)
{
	t_envvar *current;

	current = env_list;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)  // strcmp tem de passar para ft_strcmp mas nao esta feito
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void print_list_envvar(t_envvar*env_list)
{
	t_envvar *current;

	current = env_list;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

size_t calculate_final_len(const char *input, t_envvar *env_list, int exit_status)
{
	size_t len;
	const char *src;
	const char *start;
	char *var_name;
	
	(void)env_list;
	(void)exit_status;
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
			if (getenv(var_name) == NULL)
			{
				printf("%s not found\n", var_name);
				return (0);
			}
			len += strlen(getenv(var_name));
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

char	replace_envvar(const char *input, int exit_status, t_envvar *env_list)
{
	char		*result;
	size_t		len;
	const char *src;
	char 		*dst;
	//char		*exit_status_str[12];

	const char *start; // para guardar o inicio da variavel
	char		*var_name; // para guardar o nome da variavel
	const char *value; // para guardar o valor da variavel
	
	len = 0;
	src = input;
	//snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);  //ver isto ainda
	
	
	len = calculate_final_len(input, env_list, exit_status);

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
				value = getenv(var_name);
				//printf("var_name: %s...\nstart: %s...\nsrc: %s...\n", var_name, start, src);
				if (value == NULL)
				{
					printf("%s not found\n", var_name);
					return (0);
				}
				// if (value == NULL)
				// {
				// 	printf("%snao encontrado\n", var_name);
				// 	return (NULL);
				// }
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

// t_envvar_list *init_env_list()
// {
// 	t_envvar_list *env_list;

// 	env_list = (t_envvar_list *)calloc(1, sizeof(t_envvar_list)); // calloc tem de passar para ft_calloc
// 	if (env_list == NULL)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	env_list->head = NULL;
// 	return (env_list);
// }

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
	free(env_list);
}

// int main()
// {
// 	t_envvar_list *env_list;

// 	//char *input = "PATH é $PATH e HOME é $HOME e USER é $USER e PWD é $PWD 2";
// 	char *input = "PWD $PWD ";

// 	env_list = (t_envvar_list *)calloc(1, sizeof(t_envvar_list));
// 	if (env_list == NULL)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	env_list->head = NULL;
// 	set_envvar(env_list, "PATH", "/bin:/usr/bin:/usr/local/bin");
// 	set_envvar(env_list, "HOME", "/home/user");
// 	set_envvar(env_list, "USER", "user");
// 	set_envvar(env_list, "PWD", "/home/user");

// 	char *output = replace_envvar(input, 0, env_list);

// 	printf("input : %s\n", input);
// 	printf("output: %s\n", output);

// 	free_env_list(env_list);
// 	free(output);	

// 	return 0;
// }