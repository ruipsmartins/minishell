/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/17 16:26:23 by duamarqu         ###   ########.fr       */
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
	{
		printf("Unmatched quote\n");
		data->return_value = 2;
		return ;
	}
	if (ft_strchr(input, '$'))
		input = replace_envvar(input, data);
	temp = fix_token_space(input, data);
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
