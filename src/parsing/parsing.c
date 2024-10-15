/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/15 16:21:31 by addicted         ###   ########.fr       */
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
void handle_input(char *input, char **env)
{
	t_lexer *lexer = NULL;
	t_lexer *current = NULL;
	t_lexer *new_node = NULL;
	char *token = NULL;
	int i = 0;

	input = fix_token_space(input);
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
	// t_command *cmd_current = cmd_list;
	// if (1)
	// while (cmd_current != NULL)
	// {
	// 	printf("\nCommand:");
	// 	if (cmd_current->args)
	// 	{
	// 		int i = 0;
	// 		while(cmd_current->args[i] != NULL)
	// 			printf("%s ", cmd_current->args[i++]);
	// 	}
	// 	if (cmd_current->input_file)
	// 		printf("  Input: %s\n", cmd_current->input_file);
	// 	if (cmd_current->output_file)
	// 		printf("  Output: %s\n", cmd_current->output_file);
	// 	cmd_current = cmd_current->next;
	// }

		execute(cmd_list, env);
	

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