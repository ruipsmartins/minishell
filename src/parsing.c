/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:59:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/06 09:21:15 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Função para dividir a linha de comando em comando e argumentos
char	**parse_command(char *input)
{
	char	**args;
	char	*arg;
	int		i;

	args = (char **)malloc(64 * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	arg = ft_strtok(input, " ");
	while (arg)
	{
		args[i++] = arg;
		arg = ft_strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}
