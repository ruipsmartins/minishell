/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/30 11:49:27 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_token(const char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (check_if_token(str[i]))
			count++;
		i++;
	}
	if (count)
		return (count);
	return (0);
}

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

t_lexer *devide_input(char *input)
{
	t_lexer *lexer;
	t_lexer *current = NULL;
	t_lexer *new_node;
	char *token = NULL;
	int i;
	
	i = 0;
	token = ft_strtok(input, " ");
	while (token != NULL)
	{
		new_node = (t_lexer *)ft_calloc(1, sizeof(t_lexer)); // novo node
		if (new_node == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		if (is_token(token)) // Inicializar node
			new_node->token = strdup(token);
		else
			new_node->word = strdup(token);
		new_node->i = i++;
		new_node->prev = current;
		if (current != NULL) // meter node no fim da lista lista
			current->next = new_node;
		else
			lexer = new_node; // Meter o primeiro na lista
		current = new_node;
		token = ft_strtok(NULL, " ");
	}
	return (lexer);
}

void handle_input(char *input, t_data *data)
{
	t_lexer *lexer = NULL;
	t_lexer *current = NULL;
	t_envvar*env_list;

	env_list = (t_envvar *)calloc(1, sizeof(t_envvar));
	if (env_list == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// set_envvar(env_list, "PATH", "/bin:/usr/bin:/usr/local/bin");
	// set_envvar(env_list, "HOME", "/home/user");
	// set_envvar(env_list, "USER", "user");
	// set_envvar(env_list, "PWD", "/home/user");
	input = fix_token_space(input);
	input = replace_envvar(input, 0, env_list);
	lexer = devide_input(input);
	if(lexer == NULL)
	{
		printf("lexer is NULl\n");
	}

	
	//Parsing do Lexer
	t_command *cmd_list = lexer_to_command(lexer);
	execute(cmd_list, data);
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
	//free_env_list(env_list);
}

/* int main()
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
} */