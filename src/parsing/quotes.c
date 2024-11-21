/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:57:27 by addicted          #+#    #+#             */
/*   Updated: 2024/11/21 11:02:15 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote(const char *input)
{
	char c;

	c = 0;
	while(*input != '\0')
	{
		if(*input == '\'' || *input == '\"')
		{
			if(c == 0)
				c = *input;
			else if(c == *input)
				c = 0;
		}
		input++;
	}
	return((c == '\'') + (c == '\"') * 2);
}

char *fix_sapce_input(char *input)
{
	char *temp;
	int i = 0;
	int j = 0;
	char c;

	temp = calloc(strlen(input) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (input[i])
	{
		while (input[i] && input[i] != '\'' && input[i] != '\"' && !isspace(input[i]))
			temp[j++] = input[i++];
		if (input[i] == '\'' || input[i] == '\"')
		{
			c = input[i];
			temp[j++] = input[i++];
			while (input[i] && input[i] != c)
				temp[j++] = input[i++];
			temp[j++] = input[i++];
		}
		if (input[i] && isspace(input[i]))
			temp[j++] = ' ';
		while (input[i] && isspace(input[i]))
			i++;
		temp[j] = '\0';
	}
	return (temp);
}

char *in_quotes(char **input, char *word, char c)
{
	int i = 0;

	(*input)++;
	while ((*input)[i] && (*input)[i] != c)
		i++;
	word = calloc(i + 1, sizeof(char));
	if (!word)
		return (printf("failed to allocate memory\n"), NULL);
	i = 0;
	while ((*input)[i] && (*input)[i] != c)
	{
		word[i] = (*input)[i];
		i++;
	}
	word[i] = '\0';
	(*input) += i + 1;
	return (word);
}

char *no_quotes(char **input, char *word)
{
	int i = 0;

	while ((*input)[i] && !isspace((*input)[i]))
		i++;
	word = calloc(i + 1, sizeof(char));
	if (!word)
		return (printf("failed to allocate memory\n"), NULL);
	i = 0;
	while ((*input)[i] && !isspace((*input)[i]))  // passar para ft_isspace
	{
		word[i] = (*input)[i];
		i++;
	}
	word[i] = '\0';	
	(*input) += i;
	return (word);
}

char *get_word(char  **input)
{
	char *word;
	int i = 0;
	char c;


	word = NULL;
	while (**input && isspace(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	if ((*input)[i] == '\'' || (*input)[i] == '\"')
	{
		c = (*input)[i];
		word = in_quotes(input, word, c);
		c = 0;
	}
	else 
	{
		word = no_quotes(input, word);
	}
	return (word);
}