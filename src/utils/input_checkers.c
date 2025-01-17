/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:50:34 by addicted          #+#    #+#             */
/*   Updated: 2025/01/17 22:55:16 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_empty(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (input[i + 1] == input[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int	only_spaces(char *input)
{
	while (*input)
	{
		if (!isspace(*input))
			return (0);
		input++;
	}
	return (1);
}

int	start_pipe(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '|')
			return (print_error("Syntax error near unexpected token `|'\n",
					data, 2));
		else
			return (0);
	}
	return (0);
}

int	check_4_pipe(char *input, t_data *data)
{
	int		i;
	bool	quotes;

	i = 0;
	(void)quotes;
	quotes = false;
	while (i < (int)ft_strlen(input) && input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
			quotes = true;
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0')
				return (print_error("Syntax error near unexpected token `|'\n",
						data, 2));
		}
		i++;
	}
	return (0);
}

int	check_here_doc(char *input, t_data *data)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i] != '<' && input[i] != '\0')
		i++;
	if (input[i] == '<' && input[i + 1] == '<')
	{
		i += 2;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0' || input[i] == '|')
			return (print_error("Syntax error near unexpected token `<<'\n",
					data, 2));
		else
			return (0);
	}
	return (0);
}
