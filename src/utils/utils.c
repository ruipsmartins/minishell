/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:59:41 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/16 17:11:17 by ruidos-s         ###   ########.fr       */
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

void print_command_error(char *command, int error_type)
{
    if (error_type == 1) {  // "command not found"
        write(STDERR_FILENO, command, ft_strlen(command));
        write(STDERR_FILENO, ": Command not found\n", 20); // Mensagem de erro
    } 
    else if (error_type == 2) {  // "no such file or directory"
        write(STDERR_FILENO, command, ft_strlen(command));
        write(STDERR_FILENO, ": No such file or directory\n", 29); // Mensagem de erro
    }
}