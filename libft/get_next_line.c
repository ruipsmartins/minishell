/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:53:49 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/01/30 15:05:43 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE +1];
	char		*new_line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0 || FOPEN_MAX <= fd)
	{
		if (fd > 0 && FOPEN_MAX > fd)
			while (buffer[fd][i])
				buffer[fd][i++] = '\0';
		return (NULL);
	}
	new_line = NULL;
	new_line = gnl_create_line(fd, buffer[fd]);
	if (!new_line || !*new_line)
		return (NULL);
	return (new_line);
}
/*  int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;
	int		i;
	int		change_fd;
	
	i = 0;
	change_fd = 1;
	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
	while (++i)
	{
		if (change_fd > 0)
		{
			line = get_next_line(fd1);
			change_fd *= -1;
		}
		else
		{
			line = get_next_line(fd2);
			change_fd *= -1;
		}
		if (!line)
		{
			free(line);
			break ;
		}
		printf("|%d: %s", i, line);
		free(line);
	}
	return (0);
}
 */