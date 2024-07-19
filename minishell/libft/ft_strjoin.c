/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:46:33 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 18:46:30 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	newstr = (char *)malloc(s1_len + s2_len + 1);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + 1);
	ft_strlcat(newstr + s1_len, s2, s2_len + 1);
	return (newstr);
}

/*  #include <stdio.h>

 int	main(void)
{
	char *s1 = "hello ";
	char *s2 = "world!";
	char *newstr = ft_strjoin(s1, s2);

	if (newstr)
	{
		printf("Substring: %s\n", newstr);
		free(newstr);
	}

	return (0);
}  */