/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:57:45 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 15:43:08 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// return lowercase
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return (c);
}

/* 
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	printf("tolower: %c\n", tolower('R'));
	printf("ft_tolower: %c\n", ft_tolower('R'));
	return (0);
}
 */