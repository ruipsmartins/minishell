/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:00:24 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 19:33:28 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
extract substring from string

Allocates (with malloc(3)) and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len’.
*/
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	actual_len;
	char	*substring;

	if (s == NULL || start >= ft_strlen(s) || len <= 0)
		return (ft_strdup(""));
	actual_len = 0;
	while (s[start + actual_len] != '\0' && actual_len < len)
		actual_len++;
	substring = (char *)malloc(actual_len + 1);
	if (!substring)
		return (NULL);
	i = 0;
	while (i < actual_len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

/* #include <stdio.h>

int	main(void)
{
	char *original = "Hello world!";
	char *substring = ft_substr(original, 3, 5);

	if (substring)
	{
		printf("Substring: %s\n", substring);
		free(substring);
	}
	return (0);
}
  */