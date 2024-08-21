/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:08:29 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 11:32:03 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  memmove()  function  copies  n  bytes from memory area 
src to memory area dest.  The memory areas may overlap: copying takes
place as though the bytes in src are first copied
into a temporary array that does not overlap src or dest,  and  the  bytes  are
then copied from the temporary array to dest. */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	const char	*s;
	char		*d;

	d = dest;
	s = src;
	if (d == s)
		return (d);
	else if (s < d)
	{
		while (len)
		{
			len--;
			d[len] = s[len];
		}
	}
	else if (s > d)
		ft_memcpy(d, s, len);
	return (d);
}

/*  #include <stdio.h>

int    main(void)
{
   char str[] = "ABCDEFGH";

    ft_memmove(str + 2, str, 6);
    //ft_memcpy(str + 2, str, 6);
	ft_memset(str,'0', 2);

    printf("str: %s\n", str);
    return (0);
} */
