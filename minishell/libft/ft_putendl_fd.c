/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:31:32 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/22 12:04:18 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the string ’s’ to the given file descriptor
followed by a newline. */
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

/* 
#include <fcntl.h>

int	main(void)
{
	char	*str = "Hello World!!";
	int		fd;

	fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT, 0640);
	ft_putendl_fd(str, fd);
	return (0);
}
 */