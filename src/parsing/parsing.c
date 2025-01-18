/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/18 11:19:15 by ruidos-s         ###   ########.fr       */
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

void	handle_input(char *input, t_data *data)
{
	t_lexer		*lexer;
	t_command	*cmd_list;
	char		*temp;

	lexer = NULL;
	if (check_quote(input))
	{
		print_error("Unmatched quote\n", data, 2);
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
