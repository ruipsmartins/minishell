/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:07:16 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/04/18 14:43:49 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the integer ’n’ to the given file
descriptor. */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + 48, fd);
}
/* int	main(void)
{
	int		nb;
	int		fd;

	nb = -9655;
	fd = 1;
	ft_putnbr_fd(nb, fd);
	ft_putstr_fd("\n", 1);
	return (0);
} */