/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/20 11:18:27 by ruidos-s         ###   ########.fr       */
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
			{
				//printf("freeing %s\n", current->args[i]);
				free(current->args[i++]);
			}
			free(current->args);
		}
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

// void	add_new_envvar(t_data *data, char *name, char *value) //adiciona a variavel de ambiente a lista
// {
// 	char *new_env;
// 	int current_size;
	
// 	new_env = ft_strjoin(name, "=");
// 	new_env = ft_strjoin(new_env, value);
// 	printf("new_env: %s\n", new_env);															FORA DE USO
// 	current_size = 0;
// 	while (data->env[current_size] != NULL)
// 		current_size++;
// 	char **temp_env = malloc((current_size + 1) * sizeof(char *));
// 	if (temp_env == NULL)
// 	{
// 		perror("realloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	temp_env = data->env;
// 	//char *backup = temp_env[current_size];
// 	//printf("\n\nbackup: %s\n\n", backup);
// 	data->env[current_size] = new_env;
// 	//char *after = temp_env[current_size];
// 	//printf("\n\nafter: %s\n\n", after);
// 	//temp_env[current_size] = ft_strjoin(name, value);
// 	data->env[current_size + 1] = NULL;
// 	//data->env = &(*temp_env);
	
// 	printf("\n\nenv: %s\n\n", data->env[current_size]);
// 	//free(new_env);
// }

int	set_new_envvar(char *input, t_data *data)  //descobre o nome e o valor da variavel de ambiente que queremos criar
{
	char *name;
	char *value;
	int i;

	//(void)env_list;
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

	temp = fix_token_space(input);
	/* if(strchr(temp, '=')) //se tivermos um sinal de igual, quer dizer que queremos criar uma variavel de ambiente
	{
		printf("\nset new envvar\n");
		set_new_envvar(temp, data);
		data->env = swap_list_to_array(data->env_var_lst);
	} */
	if(strchr(temp, '$')) //se tivermos um sinal de dolar, quer dizer que queremos substituir uma variavel de ambiente
	{
		printf("\nreplace envvar after $\n");
		temp = replace_envvar(temp, data->env_var_lst);
	}
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
//TEMOS DE MANDA JA A NEW ENV LIST PARA A FUNCAO
	//print_list(data->env_var_lst);
	execute(cmd_list, data);
	//free_command_list(cmd_list);
	//if(data->env_var_lst)
	//	free_env_list(data->env_var_lst);
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