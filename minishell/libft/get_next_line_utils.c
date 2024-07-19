/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:25:17 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/01/30 13:17:34 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*gnl_strjoin(char *old_str, char *buffer)
{
	char		*new_str;
	size_t		i;
	size_t		j;

	new_str = malloc(gnl_strlen(old_str) + gnl_strlen(buffer) + 1);
	if (!new_str)
		return (free(old_str), NULL);
	i = 0;
	while (old_str && old_str[i])
	{
		new_str[i] = old_str[i];
		i++;
	}
	free(old_str);
	j = 0;
	while (buffer[j])
	{
		new_str[i + j] = buffer[j];
		if (buffer[j] == '\n' && ++j)
			break ;
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

void	gnl_clean_buffer(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < BUFFER_SIZE && buffer[i] != '\n')
		buffer[i++] = 0;
	if (buffer[i] == '\n')
	{
		buffer[i++] = 0;
		while (i < BUFFER_SIZE + 1)
		{
			buffer[j] = buffer[i];
			buffer[i] = 0;
			i++;
			j++;
		}
	}
}

char	*gnl_create_line(int fd, char *buffer)
{
	char	*line;

	line = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		line = gnl_strjoin(line, buffer);
		gnl_clean_buffer(buffer);
		if (line[gnl_strlen(line) - 1] == '\n')
			return (line);
	}
	return (line);
}
