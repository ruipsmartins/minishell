/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:37:23 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/08/27 15:59:06 by ruidos-s         ###   ########.fr       */
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
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	sizesrc;

	sizesrc = ft_strlen(src);
	if (!dest || !src)
		return (0);
	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size -1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (sizesrc);
}

/* #include <stdio.h>

 int	main(void)
{
	char	src[] = "Hello, World!";
	char	dest[10];
	int		len = ft_strlcpy(dest, src, sizeof(dest));

	//printf("sizeof(): %li\n",sizeof(src));
	printf("String copiada: %s\n", dest);
	printf("Tamanho da string de origem: %d\n", len);

	return (0);
}
  */