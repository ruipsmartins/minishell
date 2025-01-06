/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/06 12:37:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_token(const char *str) //Conta o numero de tokens
{
	int	i;
	int	count;

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

int	is_token(const char *str)// Define o que sao tokens
{
	int			i;
	const char	*tokens[] = {"|", ">", "<", ">>", "<<", NULL};

	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strncmp(str, tokens[i], 2) == 0)
			return (1);
		i++;
	}
	return (0);
}
// t_lexer	*devide_input(char *input) //divide a string em tokens e palavras
// {
// 	t_lexer *lexer = NULL;
// 	t_lexer *current = NULL;
// 	t_lexer *new_node;
// 	char *token = NULL;
// 	int i;
// 	i = 0;
// 	token = split_string(&input);
// 	while (token != NULL)
// 	{
// 		new_node = (t_lexer *)ft_calloc(1, sizeof(t_lexer)); // novo node
// 		if (new_node == NULL)
// 		{
// 			perror("malloc");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (is_token(token)) // Inicializar node
// 			new_node->token = ft_strdup(token);
// 		else
// 			new_node->word = ft_strdup(token);
// 		new_node->i = i++;
// 		new_node->prev = current;
// 		if (current != NULL) // meter node no fim da lista lista
// 			current->next = new_node;
// 		else
// 			lexer = new_node; // Meter o primeiro na lista
// 		current = new_node;
// 		free (token);
// 		token = split_string(&input);
// 	}
// 	free(token);
// 	return (lexer);
// }
//descobre o nome e o valor da variavel de ambiente que queremos criar

int	set_new_envvar(char *input, t_data *data)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		i++;
		if (input[i] == '=')
		{
			if (!isalnum(input[i + 1]) || !isalnum(input[i - 1]))
			{
				printf("Invalid variable name\n");
				return (0);
			}
			else
			{
				name = get_env_name(input);
				value = get_env_value(input);
			}
		}
	}
	if (name && value)
		set_envvar(data->env_var_lst, name, value);
	return (1);
}
//returns duvidosos

void	handle_input(char *input, t_data *data)
{
	t_lexer		*lexer;
	t_command	*cmd_list;
	char		*temp;

	lexer = NULL;
	if (check_quote(input))
		return ((void)printf("Unmatched quote\n"));
	if (ft_strchr(input, '$'))
		input = replace_envvar(input, data);
	temp = fix_token_space(input);
	if (temp)
		lexer = devide_input(temp);
	if (lexer == NULL)
		return (free(temp));
	cmd_list = lexer_to_command(lexer);
	free(temp);
	free_lexer(lexer);
	data->cmd = cmd_list;
	execute(cmd_list, data);
	free_command_list(cmd_list);
}
