/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:31:31 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/26 15:06:41 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//write zeroes to a byte string.
void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, '\0', len);
}

/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "Hello World!";

	printf("antes do ft_bzero: %s\n", str);
	ft_bzero(str + 5, 5);
	printf("depois do ft_bzero: %s\n", str);
	return (0);
}
 */