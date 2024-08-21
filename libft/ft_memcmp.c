/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:12:26 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/16 11:49:52 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The memcmp() function compares the first n bytes
(each interpreted as unsigned char) of the memory areas s1 and s2. */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/* int	main(void)
{
	printf("memcmp: %d\n", memcmp("teste", "testex", 6));
	printf("ft_memcmp: %d\n", ft_memcmp("teste", "testex", 6));
	return (0);
}
 */