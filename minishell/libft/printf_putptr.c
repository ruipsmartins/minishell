/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:02:31 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/01/30 12:13:17 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_putptr(unsigned long nbr, int base, int reset)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	count = 0;
	if (reset == 1)
	{
		if (nbr == 0)
			return (printf_putstr("(nil)"));
		count += printf_putstr("0x");
	}
	if (nbr < (unsigned long)base)
	{
		printf_putchar(symbols[nbr]);
		count++;
	}
	else
	{
		count += printf_putptr(nbr / base, base, 0);
		count += printf_putptr(nbr % base, base, 0);
	}
	return (count);
}
