/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:49:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/26 14:55:33 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//checks for any printable character including space.

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
	printf("%d\n", ft_isprint(30));

	int c;
	for(c = 1; c <= 127; ++c)
   	if (ft_isprint(c)!= 0)
             printf("%c ", c);
   return 0;
}
*/