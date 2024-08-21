/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:33:15 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/01/30 12:13:27 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the string ’s’ to the given file
descriptor. */
#include "libft.h"

int	printf_putstr(char *s)
{
	int	count;

	count = 0;
	if (s == NULL)
		s = ("(null)");
	while (*s)
	{
		printf_putchar(*s++);
		count++;
	}
	return (count);
}
