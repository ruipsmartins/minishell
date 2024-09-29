/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/29 14:59:11 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_token(const char *str)
{
	int i = 0;
	int k = 0;
	int token = 0;
	const char *tokens[] = {"|", ">", "<", "&", NULL};
	while (str[i])
	{
		k = 0;
		while (tokens[k])
		{
			if (str[i] == tokens[k][0])
			{
				// printf("i = %d\n", i);
				// printf("tokens[k] = %s\n", tokens[k]);
				token++;
			}
			k++;
		}
		i++;
	}
	if (token)
	{
		// printf("token found: %d\n", token);
		return (token);
	}
	return 0;
}
char *fix_token_space(char *str)
{
	int i = 0;
	int k = 0;
	int t = 0;
	int max_len = strlen(str) + count_token(str) + 3;
	const char *tokens[] = {"|", ">", "<", "&", NULL};
	char *fixed_str = malloc(max_len);
	while (str[i] && t < max_len -1) 
	{
		k = 0;
		while (tokens[k])
		{
			if (str[i] == tokens[k][0])
			{
				fixed_str[t] = ' ';
				t++;
				fixed_str[t] = str[i];
				if (str[i + 1] == tokens[k][0])
				{
					i++;
					t++;
					fixed_str[t] = str[i];
				}
				else if (str[i + 1] != tokens[k][0] && str[i + 1])
				{
					t++;
					fixed_str[t] = ' ';
				}
				i++;
				t++;
			}
			k++;
		}
		fixed_str[t] = str[i];
		t++;
		i++;
	}
	fixed_str[t] = '\0';
	
	return (fixed_str);
}

char *ft_strtok(char *str, const char *delim)
{
	static char *last;
	char *start;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	while (*last && strchr(delim, *last))
		last++;
	if (!*last)
		return (NULL);
	while (*last && strchr(delim, *last))
		last++;
	start = last;
	while (*last && !strchr(delim, *last))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;
	return (start);
}

void *ft_calloc(size_t count, size_t size)
{
	void *ptr = malloc(count * size);
	if (ptr)
		memset(ptr, 0, count * size);
	return ptr;
}

char *strdup(const char *s)
{
	if (s == NULL)
		return NULL;
	char *d = malloc(strlen(s) + 1); // +1 for the null-terminator
	if (d == NULL)
		return NULL; // No memory
	strcpy(d, s);	 // Copy the string
	return d;		 // Return the new string
}

// void *ft_realloc(void *ptr, size_t size)
// {
// 	void *new_ptr;

// 	if (ptr == NULL)
// 		return (malloc(size));
// 	if (!size)
// 		return (ptr);
// 	new_ptr = malloc(size);
// 	ft_memcpy(new_ptr, ptr, size);
// 	return (new_ptr);
// }
//
// Define o que sao tokens

int is_token(const char *str)
{
	int i = 0;
	const char *tokens[] = {"|", ">", "<", ">>", "<<", NULL};
	while (tokens[i] != NULL)
	{
		if (strncmp(str, tokens[i], 2) == 0) //testar o strncmp com o 2
			return 1;
		i++;
	}
	return 0;
}
// int fix_token(char *str)
// {
// 	int i = 0;
// 	int k = 0;
// 	const char *tokens[] = {"|", ">", "<", ">>", "<<", NULL};
// 	while (str[i] != NULL)
// 	{
// 		k = 0;
// 		while(tokens[k])
// 		{
// 			if (str[i] == tokens[k])
// 			{
// 				str[i] = ' ';
// 				return(tokens[k] + '0');
// 			}
// 			k++;	
// 		}
// 		i++;
// 	}
// 	return 0;
// }

t_command *lexer_to_command(t_lexer *lexer)
{
	t_command *cmd_list = NULL;
	t_command *current_cmd = NULL;
	t_lexer *current = lexer;
	int arg_count = 0;

	while (current != NULL)
	{
		if (current->token && strncmp(current->token, "|", 2) == 0)
		{
			// Handle pipe: criar novo comando
			current_cmd->next = (t_command *)ft_calloc(1, sizeof(t_command));
			current_cmd = current_cmd->next;
			arg_count = 0;
		}
		else if (current->token && strncmp(current->token, ">", 2) == 0)//
		{
			// Handle output redirection
			current = current->next;
			if (current && current->word)
				current_cmd->output_file = strdup(current->word);
		}
		else if (current->token && strncmp(current->token, "<", 2) == 0)//
		{
			// Handle input redirection
			current = current->next;
			if (current && current->word)
				current_cmd->input_file = strdup(current->word);
		}
		else
		{
			// Handle command arguments
			if (arg_count == 0)
			{
				// Crear primeiro commando
				if (cmd_list == NULL)
				{
					cmd_list = (t_command *)ft_calloc(1, sizeof(t_command));
					current_cmd = cmd_list;
				}
				else if (current_cmd == NULL)
				{
					current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
				}
			}
			current_cmd->args = (char **)realloc(current_cmd->args, sizeof(char *) * (arg_count + 2));
			current_cmd->args[arg_count] = strdup(current->word);
			current_cmd->args[arg_count + 1] = NULL;
			arg_count++;
		}
		current = current->next;
	}

	return cmd_list;
}

void free_command_list(t_command *cmd_list)
{
	int i;
	t_command *current;
	t_command *next;
	
	current = cmd_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i] != NULL)
				free(current->args[i++]);
			free(current->args);
		}
		free(current->input_file);
		free(current->output_file);
		free(current);
		current = next;
	}
}
void handle_input(char *input, char **env)
{
	t_lexer *lexer = NULL;
	t_lexer *current = NULL;
	t_lexer *new_node = NULL;
	char *token = NULL;
	int i = 0;

	token = ft_strtok(input, " ");
	while (token != NULL)
	{
		// novo node
		new_node = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
		if (new_node == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		// Inicializar node
		if (is_token(token))
		{

			new_node->token = strdup(token);
			new_node->word = NULL;
		}
		else
		{
			new_node->word = strdup(token);
			new_node->token = NULL;
		}
		new_node->i = i++;
		new_node->next = NULL;
		new_node->prev = current;

		// meter node no fim da lista lista
		if (current != NULL)
		{
			current->next = new_node;
		}
		else
		{
			lexer = new_node; // Meter o primeiro na lista
		}
		current = new_node;

		//obter o seguinte token
		token = ft_strtok(NULL, " ");
	}

	//Parsing do Lexer
	t_command *cmd_list = lexer_to_command(lexer);

	// Imprimir os comandos do parsing
	t_command *cmd_current = cmd_list;
	while (cmd_current != NULL)
	{
		printf("\nCommand:");
		if (cmd_current->args)
		{
			int i = 0;
			while(cmd_current->args[i] != NULL)
				printf("%s ", cmd_current->args[i++]);
		}
		if (cmd_current->input_file)
			printf("  Input: %s\n", cmd_current->input_file);
		if (cmd_current->output_file)
			printf("  Output: %s\n", cmd_current->output_file);
		cmd_current = cmd_current->next;
	}

	//Free da lista dos comandos
	free_command_list(cmd_list);
	current = lexer;
	while (current != NULL)
	{
		t_lexer *next = current->next;
		free(current->word);
		free(current->token);
		free(current);
		current = next;
	}
}

int main()
{
	char *input = "<ls -la|grep worln<d  0123|45 ii9|i|iiiii";
	char *env[] = {NULL}; // Dummy environment

	printf("strlen: %d\n", (int)strlen(input));
	printf("input:\n%s\n", input);
	input = fix_token_space(input);
	printf("input after:\n%s\n", input);
	//linha para ver se sei fazer
	handle_input(input, env);
	free(input);

	return 0;
}