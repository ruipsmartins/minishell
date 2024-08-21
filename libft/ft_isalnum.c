/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:34:41 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/26 14:52:15 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* checks for an alphanumeric character; it is
 equivalent to (isalpha(c) || isdigit(c)). */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
		printf("%d\n", ft_isalnum('5'));
		printf("%d\n", isalnum('5'));
}
*/