/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:08:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 16:09:14 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strcmp()  function compares the two strings s1 and s2.
The strncmp() function is similar, except it 
compares only the first (at most) n bytes of s1 and s2. */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
/* #include <stdio.h>

 int	main(void)
{
	printf("strncmp: %d\n", strncmp("abc", "abc", 7));
	printf("ft_strncmp: %d\n", ft_strncmp("abc", "abc", 7));

	printf("strncmp: %d\n", strncmp("abcdef", "abc\375xx", 5));
    printf("ft_strncmp: %d\n", ft_strncmp("abcdef", "abc\375xx", 5));
	return (0);
}  */