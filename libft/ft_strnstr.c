/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:38:25 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 17:52:23 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strnstr() function locates the first occurrence
of the null-terminated string little in the string big,
where not more than len characters are searched.  
Characters that appear after a ‘\0’ character are not searched.
Since the strnstr() function is a
FreeBSD specific API, it should only be used 
when portability is not a concern. */
//Utility functions from BSD systems (libbsd, -lbsd)

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	if (!*big)
		return (NULL);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

/* #include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	*big = "isto um e uma mensagem";
	char	*lil = "uma";
	size_t	len = 15;

	printf("strnstr: %s\n", strnstr(big, lil, len));
	printf("ft_strnstr: %s\n", ft_strnstr(big, lil, len));

	return (0);
} */