/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:32:40 by addicted          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:16 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *skip_spaces(char *input)
{
	while (isspace(*input))
		input++;
	return input;
}

// Retorna o próximo token e avança a entrada
char *split_string(char **input)
{
	if (!*input || **input == '\0')
		return NULL;

	char *start = skip_spaces(*input); // Ignora espaços no início
	char *output = malloc((ft_strlen(start) + 1) * sizeof(char));
	char *output_ptr = output;

	int in_single = 0, in_double = 0;

	while (*start && (!isspace(*start) || in_single || in_double))
	{
		if (*start == '\'' && !in_double)
			in_single = !in_single; // Alterna estado de aspas simples
		else if (*start == '"' && !in_single)
			in_double = !in_double; // Alterna estado de aspas duplas
		else
			*output_ptr++ = *start; // Copia caractere para o token

		start++;
	}

	*output_ptr = '\0';			 // Finaliza a string do token
	*input = skip_spaces(start); // Atualiza o ponteiro de entrada

	return output;
}
