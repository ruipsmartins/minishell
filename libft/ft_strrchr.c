/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:17:46 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 16:06:29 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  The strrchr() function returns a pointer
 to the last occurrence of the character c in the string s. */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (s[i] != (char)c)
	{
		if (i < 0)
			return (NULL);
		i--;
	}
	return ((char *)&s[i]);
}

/* #include <stdio.h>

 int	main(void)
{
	printf("strrchr: %s\n", strrchr("teste 123 ", 'e'));
	printf("ft_strrchr: %s\n", ft_strrchr( "teste 123", 'e'));
	return (0);
}  */