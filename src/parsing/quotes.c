/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:57:27 by addicted          #+#    #+#             */
/*   Updated: 2025/01/17 18:12:50 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote(const char *input)
{
	char	c;

	c = 0;
	while (*input != '\0')
	{
		if (*input == '\'' || *input == '\"')
		{
			if (c == 0)
				c = *input;
			else if (c == *input)
				c = 0;
		}
		input++;
	}
	return ((c == '\'') + (c == '\"') * 2);
}

int	in_quotes_check(char *str, int pos)
{
	char	c;
	int		i;
	bool	quotes;

	quotes = false;
	i = 0;
	c = '\0';
	while (str[i] && i <= pos)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (c == '\0')
			{
				c = str[i];
				quotes = true;
			}
			else if (c == str[i])
			{
				c = '\0';
				quotes = false;
			}
		}
		i++;
	}
	return (quotes);
}

char	*skip_spaces(char *input)
{
	while (isspace(*input))
		input++;
	return (input);
}

// Retorna o próximo token e avança a entrada

void	copy_token(char **start, char **output_ptr,
t_quotes *quotes)
{
	while (*(*start) && (!isspace(*(*start))
			|| quotes->in_single || quotes->in_double))
	{
		if (*(*start) == '\'' && !quotes->in_double)
			quotes->in_single = !quotes->in_single;
		else if (*(*start) == '\"' && !quotes->in_single)
			quotes->in_double = !quotes->in_double;
		else
			*(*output_ptr)++ = *(*start);
		(*start)++;
		if (quotes->in_double || quotes->in_single)
			quotes->quotes = 1;
	}
}

char	*split_string(char **input, t_quotes *quotes)
{
	char	*start;
	char	*output;
	char	*output_ptr;

	if (!*input || **input == '\0' || !input)
		return (NULL);
	start = skip_spaces(*input);
	output = malloc((ft_strlen(start) + 1) * sizeof(char));
	output_ptr = output;
	copy_token(&start, &output_ptr, quotes);
	*output_ptr = '\0';
	*input = skip_spaces(start);
	return (output);
}
