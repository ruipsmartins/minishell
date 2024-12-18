/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/18 17:02:01 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_token(const char *str) //Conta o numero de tokens
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

int is_token(const char *str)// Define o que sao tokens
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

void free_command_list(t_command *cmd_list) //free da lista de comandos
{
	int i;
	t_command *current = NULL; 
	t_command *next;
	
	current = cmd_list;
	while (current != NULL)
	{
		//printf("freeing command\n");
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i] != NULL)
			{
				free(current->args[i++]);
			}			free(current->args);
		}
		if (current->heredoc)
			free(current->delimiter);
		free(current->input_file);
		free(current->output_file);
		free(current);
		current = next;
	}
}

t_lexer *devide_input(char *input) //divide a string em tokens e palavras
{
	t_lexer *lexer;
	t_lexer *current = NULL;
	t_lexer *new_node;
	char *token = NULL;
	int i;
	
	i = 0;
	token = split_string(&input);
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
		free (token);
		token = split_string(&input);
	}
	free(token);
	return (lexer);
}


char	*get_env_name(char  *input) //descobre o nome da variavel de ambiente que queremos criar
{
	int i;
	int k;

	i = 0;
	while(input[i] != '=' && input[i] != '\0')
		i++;
	k = i - 1;
	if (!isalnum(input[i + 1]) || !isalnum(input[i - 1]))
	{
		printf("Invalid variable name\n");
		return (NULL);
	}
	while(k > 0 && input[k] && (isalnum(input[k-1]) || input[k - 1] == '_'))
		k--;
	return (strndup(input + k, i - k));  // passar para ft_strndup
}

char	*get_env_value(char *input)	//descobre o valor da variavel de ambiente que queremos criar
{
	int i;
	int k;
	
	i = 0;
	while(input[i] != '=' && input[i] != '\0')
		i++;
	k = i + 1;
	while(input[k] && input[k] != ' ')
		k++;
	return (strndup(input+i+1, k));  // passar para ft_strndup
}

//descobre o nome e o valor da variavel de ambiente que queremos criar
int	set_new_envvar(char *input, t_data *data)  
{
	char *name;
	char *value;
	int i;

	i = 0;
	while(input[i] != '\0')
	{
		i++;
		if(input[i] == '=')
		{
			if(!isalnum(input[i+1]) || !isalnum(input[i-1]))
			{
				printf("Invalid variable name\n");
				return(0);
			}
			else
			{
				name = get_env_name(input);
				value = get_env_value(input);
			}
		}
	}
	if(name && value)
		set_envvar(data->env_var_lst, name, value);
	return(1);
}

void free_lexer(t_lexer *lexer)
{
	t_lexer *current = lexer;
	t_lexer *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		free(current->word);
		free(current->token);
		current->next = NULL;
		free(current);
		current = next;
	}
	//free(lexer);
}

void handle_input(char *input, t_data *data)
{
	t_lexer *lexer = NULL;

	char *temp;
	if(check_quote(input))
	{
		printf("Error: Unmatched quote\n");
		input = readline("minishell: ");
	}
	if(strchr(input, '$')) //se tivermos um sinal de dolar, quer dizer que queremos substituir uma variavel de ambiente
	{
		//printf("\nreplace envvar after $\n");
		input = replace_envvar(input, data);
	}
	
	temp = fix_token_space(input);
	lexer = devide_input(temp);
	
	if(lexer == NULL)
	{
		printf("lexer is NULl\n");
	}
	//Parsing do Lexer
	t_command *cmd_list = lexer_to_command(lexer);
	free(temp);
	free_lexer(lexer);
	data->cmd = cmd_list;
	execute(cmd_list, data);
	free_command_list(cmd_list);
}
