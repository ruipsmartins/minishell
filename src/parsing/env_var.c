/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2024/10/19 12:48:19 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void set_envvar(t_envvar_list *envvar_list, const char *name, const char *value)
{
	t_envvar *current;
	t_envvar *prev;
	t_envvar *new_var;

	current = envvar_list->head;
	prev = NULL;
	while (current != NULL) // verificar se a variavel exitste
	{
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
		envvar_list->head = new_var;
	else
		prev->next = new_var;
}
char *get_envvar(t_envvar_list *env_list, const char *name)
{
	t_envvar *current;

	current = env_list->head;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void print_list_envvar(t_envvar_list *env_list)
{
	t_envvar *current;

	current = env_list->head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}

char	*replace_envvar(const char *input, int exit_status, t_envvar_list *env_list)
{
	char		*result;
	size_t		len;
	const char *src;
	char 		*dst;
	char		*exit_status_str[12];

	const char *start; // para guardar o inicio da variavel
	char		*var_name; // para guardar o nome da variavel
	const char *value; // para guardar o valor da variavel
	
	len = 0;
	src = input;
	//snprintf(exit_status_str, sizeof(exit_status_str), "%d", exit_status);  //ver isto ainda
	
	//calcular o tamanho das variaveis
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
				while(*src && (isalnum(*src) || *src == '_')) //passar para ft_isalnum
					src++;
				var_name = strndup(start, src - start); // passar para ft_strndup
				value = get_envvar(env_list, var_name);
				if (value == NULL)
				{
					printf("%s nao encontrado\n", var_name);
					return(NULL);
				}
				len += strlen(value);
				free(var_name);
			}
		}
		else
		{
			len++;
			src++;
		}
	}

	//alocar memoria para a string final
	result = (char *)calloc(len + 1, sizeof(char)); // calloc tem de passar para ft_calloc
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
				start == ++src;
				while(*src && (isalnum(*src) || *src == '_')) //passar para ft_isalnum
					src++;
				var_name = strndup(start, src - start); // passar para ft_strndup
				value = get_envvar(env_list, var_name);
				if (value == NULL)
				{
					printf("%s nao encontrado\n", var_name);
					return (NULL);
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

t_envvar_list *init_env_list()
{
	t_envvar_list *env_list;

	env_list = (t_envvar_list *)calloc(1, sizeof(t_envvar_list)); // calloc tem de passar para ft_calloc
	if (env_list == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	env_list->head = NULL;
	return (env_list);
}

int main()
{
	// char *input = "<ls -la|grep worln<d  0123|45 ii9|i|iiiii";
	// char *env[] = {NULL}; // Dummy environment
	t_envvar_list *env_list;

	char *input = "PATH é $PATH e HOME é $HOME e USER é $USER e PWD é $PWD";

	env_list = (t_envvar_list *)calloc(1, sizeof(t_envvar_list));
	if (env_list == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	env_list->head = NULL;
	set_envvar(env_list, "PATH", "/bin:/usr/bin:/usr/local/bin");
	set_envvar(env_list, "HOME", "/home/user");
	set_envvar(env_list, "USER", "user");
	set_envvar(env_list, "PWD", "/home/user");

	//print_list_envvar(env_list);

	printf("input : %s\n", input);
	printf("output: %s\n", replace_envvar(input, 0, env_list));

	
	// printf("strlen: %d\n", (int)strlen(input));
	// printf("input:\n%s\n", input);
	// input = fix_token_space(input);
	// printf("input after:\n%s\n", input);
	// linha para ver se sei fazer
	// handle_input(input, env);
	// free(input);

	return 0;
}