/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:50:34 by addicted          #+#    #+#             */
/*   Updated: 2025/01/17 12:23:19 by duamarqu         ###   ########.fr       */
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
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '|')
		{
			data->return_value = 2;
			ft_printf("START_PIPE:Syntax error near unexpected token `|'\n");
			return (0);
		}
		else
			return (1);
	}
	return (1);
}

int	check_4_pipe(char *input, t_data *data)
{
	int	i;
	bool quotes;
	
	i = 0;
	quotes = false;
	if (!start_pipe(input, data))
		return (1);
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if(input[i] == '\'' || input[i] == '\"')
			quotes = true;
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0')// && !quotes)
			{
				data->return_value = 2;
				return (ft_printf("CHECK_4_PIPE:Syntax error near unexpected token `|'\n"));
			}
		}
		if (input[i] != '\0')
			i++;
	}
	return (0);
}

int	check_here_doc(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] != '<' && input[i] != '\0')
		i++;
	if (input[i] == '<' && input[i + 1] == '<')
	{
		i += 2;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0' || input[i] == '|')
		{
			data->return_value = 2;
			return (ft_printf("CHECK_HERE_DOC:Syntax error near unexpected token `<<'\n"));
		}
		else
			return (0);
	}
	return (0);
}
