/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:03:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 16:24:53 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  memchr()  function scans the initial n bytes of the memory
area pointed to by s for the first instance of c.  Both c and the
bytes of the memory area pointed to by s are interpreted as unsigned char. */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
/* #include <stdio.h>

 int	main(void)
{
	printf("strchr: %p\n", memchr("teste", 'e', 3));
	printf("ft_strchr: %p\n", ft_memchr( "teste", 'e', 3));
	return (0);
}
 */