/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:34:30 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/01/30 12:12:59 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += printf_putchar(va_arg(ap, int));
	else if (specifier == 's')
		count += printf_putstr(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += printf_putnbr(va_arg(ap, int), 10, 0);
	else if (specifier == 'u')
		count += printf_putnbr(va_arg(ap, unsigned int), 10, 0);
	else if (specifier == 'x')
		count += printf_putnbr(va_arg(ap, unsigned int), 16, 0);
	else if (specifier == 'X')
		count += printf_putnbr(va_arg(ap, unsigned int), 16, 1);
	else if (specifier == 'p')
		count += printf_putptr(va_arg(ap, unsigned long), 16, 1);
	else
		count += write(1, &specifier, 1);
	return (count);
}
