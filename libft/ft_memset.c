/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 09:47:37 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/26 15:38:16 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 	The memset() function fills the first n bytes of the memory
	area pointed to by s with the constant byte c. */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	while (len--)
		((char *)s)[len] = (char)c;
	return (s);
}

/*
#include <stdio.h>

int    main(void)
{
    char    str[] = "Hello World!";
	int		numbers[5];

    printf("antes do ft_memset: %s\n", str);
    ft_memset(str,'X', 5);
    printf("depois do ft_memset: %s\n", str);

    ft_memset(numbers, 0, sizeof(numbers));
    
    for (int i = 0; i < 5; ++i) {
        printf("%d ", numbers[i]);
    }
    
    return (0);
} */