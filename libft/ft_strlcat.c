/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:12:46 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/30 14:15:31 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The strlcpy() and strlcat() functions copy and concatenate strings 
respectively.  They are designed to be safer, more consistent,
and less error prone replacements for strncpy(3) and strncat(3).
Unlike those functions, strlcpy() and strlcat() take the full
ize of the buffer (not just the length) and guarantee to NUL-terminate 
the result (as long as size is larger than 0 or, in the
case of strlcat(), as long as there is at least one byte free in dst).
Note that a byte for the NUL should be included in size.
Also note that strlcpy() and strlcat() only operate on true “C” strings.
This means that for strlcpy() src must be NUL-terminated
and for strlcat() both src and dst must be NUL-terminated */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (size <= ft_strlen(dest))
		return (ft_strlen(src) + size);
	i = 0;
	j = ft_strlen(dest);
	while (src[i] != '\0' && j + 1 < size)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (ft_strlen(dest) + ft_strlen(&src[i]));
}

/* #include <stdio.h>

int	main(void)
{
	char dest[20] = "Hello, ";
    char src[] = "World!";

    size_t len = ft_strlcat(dest, src, 18);

    printf("String concatenada: %s\n", dest);
    printf("Tamanho da string resultante: %zu\n", len);
	return (0);
}  */