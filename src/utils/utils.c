/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:59:41 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/29 15:35:11 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Função para dividir strings (melhorias strtok, remove todos os espaços)
char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*start;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	if (!*last)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	start = last;
	while (*last && !ft_strchr(delim, *last))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;
	return (start);
}

// Função para fechar os file descriptors
/* void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
} */

void	print_command_error(t_data *data,char *command, int error_type)
{
	if (error_type == 1)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": Command not found\n", 20);
		data->return_value = 127;
	}
	else if (error_type == 2)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		data->return_value = 1;
	}
}