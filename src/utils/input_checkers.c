/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:50:34 by addicted          #+#    #+#             */
/*   Updated: 2025/01/05 17:58:36 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_spaces(char *input)
{
	while (*input)
	{
		if (!isspace(*input) && *input != '\'' && *input != '\"')
			return (0);
		input++;
	}
	return (1);
}

int	check_4_pipe(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0')
			{
				data->return_value = 2;
				return (ft_printf("Syntax error near unexpected token `|'\n"));
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
			return (ft_printf("Syntax error near unexpected token `<<'\n"));
		}
		else
			return (0);
	}
	return (0);
}
