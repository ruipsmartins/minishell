/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:46:42 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/30 11:32:17 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/* 
#include <stdio.h>

void	ft_teste(unsigned int i, char*c)
{

	if (*c >= 'a' && *c <= 'z')
	{
		*c -= 32;
		printf("i = %i, Char: %c\n", i, *c);
	}
}

int	main(void)
{
	char	str[] = "hello world!!";

	printf("Original String: %s\n", str);
	ft_striteri(str, ft_teste);
	printf("Modified String: %s\n", str);
	return (0);
}

 */