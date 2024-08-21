/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:17:46 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 19:39:31 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strchr() function returns a pointer to the 
	first occurrence of the character c in the string s. */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("strchr: %s\n", strchr("teste", 101));
	printf("ft_strchr: %s\n", ft_strchr( "101teste", 'e'));
	return (0);
}
 */