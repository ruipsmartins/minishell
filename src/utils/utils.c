/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:59:41 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/16 13:17:53 by ruidos-s         ###   ########.fr       */
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

void	print_command_error(t_data *data, char *command, int error_type)
{
	if (error_type == 127)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": Command not found\n", 20);
		data->return_value = 127;
	}
	else if (error_type == 1)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": No such file or directory\n", 29);
		data->return_value = 1;
	}
	else if (error_type == 126)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		data->return_value = 126;
	}
}


int	check_file_type(char *path)
{
	struct stat path_stat;
	if (stat(path, &path_stat) != 0)
		return (-1);
	if (S_ISDIR(path_stat.st_mode))
		return (126);
	if (!S_ISREG(path_stat.st_mode) || access(path, X_OK) != 0)
		return (126);
	return (0);
}


