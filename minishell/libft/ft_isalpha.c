/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:40:06 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/26 13:50:40 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* checks for an alphabetic character;
 in the standard "C" locale, it is equivalent to (isupper(c) || islower(c)). */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main()
{
		printf("%d\n", ft_isalpha('Z'));
		printf("%d\n", isalpha('Z'));
		printf("%d\n", isalpha(38463));
}
*/