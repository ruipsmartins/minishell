/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:57:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/01/30 12:13:09 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

int	printf_putnbr(long nbr, int base, int upper)
{
	char	*symbols;
	int		count;

	symbols = "0123456789abcdef";
	count = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		return (printf_putnbr(-nbr, base, upper) + 1);
	}
	if (nbr < base)
	{
		if (upper == 1)
			return ((printf_putchar(printf_toupper(symbols[nbr]))));
		return (printf_putchar(symbols[nbr]));
	}
	else
	{
		count = printf_putnbr(nbr / base, base, upper);
		return (count + printf_putnbr(nbr % base, base, upper));
	}
}
