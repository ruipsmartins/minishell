/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:57:45 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 15:42:11 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//return uppercase
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}

/* #include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("toupper: %c\n", toupper('r'));
	printf("ft_toupper: %c\n", ft_toupper('r'));
	return (0);
}
 */