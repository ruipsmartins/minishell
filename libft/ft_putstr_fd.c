/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:33:15 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/22 11:28:45 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the string ’s’ to the given file
descriptor. */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}

/* 
#include <fcntl.h>
int	main(void)
{
	char	*str = "Hello World!!\n";
	int		fd;

	fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT, 0640);
	ft_putstr_fd(str, fd);
	return (0);
}
 */