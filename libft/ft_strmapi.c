/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:05:26 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/30 11:29:22 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’. */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*result;
	unsigned int		i;

	result = (char *)malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
#include <stdio.h>
char	ft_teste(unsigned int i, char c)
{
	i = 32;
	if (c >= 'a' && c <= 'z')
	{
		c -= i;
	}
	return (c);
}

int	main(void)
{
	char	*str = "hello world!!";
	char	*result;

	result = ft_strmapi(str, ft_teste);
	printf("ft_strmapi: %s\n", result);
	free(result);
	return (0);
}  */