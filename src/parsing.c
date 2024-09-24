/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/24 12:59:55 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char *ft_strdup(const char *s)
{
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
	const char *tokens[] = {"|", ">", "<", "&&", "||", NULL};
	while (tokens[i] != NULL)
	{
		if (strcmp(str, tokens[i]) == 0)
			return 1;
		i++;
	}
	return 0;
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
			new_node->token = ft_strdup(token);
			new_node->word = NULL;
		}
		else
		{
			new_node->word = ft_strdup(token);
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

	// imprimir a lista para ver se esta a funcionar
	current = lexer;
	while (current != NULL)
	{
		//printf("index = %d\n", current->i);
		if (current->word)
			printf("Word: %s\n", current->word);
		if (current->token)
			printf("Token: %s\n", current->token);
		current = current->next;
	}
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
	char input[] = "ls -la | grep world > output.txt";
	char *env[] = {NULL}; // Dummy environment
	handle_input(input, env);
	return 0;
}

	// void	handle_input(char *input, char **env)
	// {
	// 	char	**args;
	// 	char	*command;
	// 	char	***commands;
	// 	int		i;

	// 	if (ft_strchr(input, '|'))
	// 	{
	// 		commands = split_by_pipe(input);
	// 		execute_piped_commands(commands, env);
	// 		i = 0;
	// 		// Liberação de memória dos comandos
	// 		while (commands[i])
	// 		{
	// 			free(commands[i]);
	// 			i++;
	// 		}
	// 		free(commands);
	// 	}
	// 	else
	// 	{
	// 		args = parse_command(input);
	// 		if (!args)
	// 			return ;
	// 		command = args[0];
	// 		execute_path(command, args, env);
	// 		free(args);
	// 	}
	// }

	// Função para dividir a linha de comando em comando e argumentos
// 	char **parse_command(char *input)
// {
// 	char	**args;
// 	char	*arg;
// 	int		buf_size = BUFFER_SIZE;
// 	int		i;
// 	void *ft_realloc(void *ptr, size_t size)
// 	{
// 		void *new_ptr;

// 		if (ptr == NULL)
// 			return (malloc(size));
// 		if (!size)
// 			return (ptr);
// 		new_ptr = malloc(size);
// 		ft_memcpy(new_ptr, ptr, size);
// 		return (new_ptr);
// 	}
// 	args = (char **)malloc(buf_size * sizeof(char *));
// 	if (!args)
// 		return (NULL);
// 	i = 0;
// 	arg = ft_strtok(input, " ");
// 	while (arg)
// 	{
// 		if(i = buf_size)
// 		{
// 			buf_size += BUFFER_SIZE;
// 			args = ft_realloc()
// 		}
// 		args[i++] = arg;
// 		arg = ft_strtok(NULL, " ");
// 	}
// 	args[i] = NULL;
// 	return (args);
// }
