/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:11:06 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/22 10:32:24 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the character ’c’ to the given file
descriptor. */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int	main(void)
{
	char	c;

	c = 'z';
	ft_putchar_fd(c, 1);
	return (0);
}
 */