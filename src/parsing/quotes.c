/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:57:27 by addicted          #+#    #+#             */
/*   Updated: 2025/01/17 16:05:27 by duamarqu         ###   ########.fr       */
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

char	*skip_spaces(char *input)
{
	while (isspace(*input))
		input++;
	return (input);
}

// Retorna o próximo token e avança a entrada

void	copy_token(char **start, char **output_ptr,
int *in_single, int *in_double, int *was_in_quotes)
{
	while (*(*start) && (!isspace(*(*start)) || *in_single || *in_double))
	{
		if (*(*start) == '\'' && !*in_double)
			*in_single = !*in_single;
		else if (*(*start) == '\"' && !*in_single)
			*in_double = !*in_double;
		else
			*(*output_ptr)++ = *(*start);
		(*start)++;
		if(*in_single || *in_double)
			*was_in_quotes = 1;
	}
}

char	*split_string(char **input, int *was_in_quotes)
{
	char	*start;
	char	*output;
	char	*output_ptr;
	int		in_single = 0;
	int		in_double = 0;


	if (!*input || **input == '\0' || !input)
		return (NULL);
	start = skip_spaces(*input);
	output = malloc((ft_strlen(start) + 1) * sizeof(char));
	output_ptr = output;
	copy_token(&start, &output_ptr, &in_single, &in_double, was_in_quotes);
	*output_ptr = '\0';
	*input = skip_spaces(start);
	return (output);
}
