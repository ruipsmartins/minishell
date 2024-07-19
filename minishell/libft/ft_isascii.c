/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:25:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/26 14:53:19 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* checks whether c is a 7-bit unsigned char value that
 fits into the ASCII character set. */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
		printf("%d\n", ft_isascii('/'));
		printf("%d\n", isascii('/'));
}
 */