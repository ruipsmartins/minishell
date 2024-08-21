/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:09:43 by ruidos-s          #+#    #+#             */
/*   Updated: 2023/10/27 18:26:27 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The calloc() function allocates memory for an array of nmemb 
elements of size bytes each and returns a pointer to  the  allocated
       memory.  The memory is set to zero.  */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	total;

	total = nmemb * size;
	dest = malloc(total);
	if (!dest)
		return (0);
	ft_bzero(dest, total);
	return (dest);
}

/* #include <stdio.h>

int	main(void)
{
	int		*array1;
	int		*array2;
	size_t	num_elements = 10;
	size_t	i;
	int		*junk;

	junk = malloc(10*sizeof(int));

	for (size_t i = 0; i < 10; i++)
	{
		junk[i] = i;
	}
	free(junk);

	array1 = (int *)ft_calloc(num_elements, sizeof(int));
	array2 = (int *)calloc(num_elements, sizeof(int));

	i = 0;
	printf("Array1 com zeros: ");
	while (i < num_elements)
	{
		printf("%d ", array1[i]);
		i++;
	}
	printf("\nArray2 com zeros: ");
	i = 0;
	while (i < num_elements)
	{
		printf("%d ", array2[i]);
		i++;
	}
	printf("\n");
	free(array1);
	free(array2);

	return (0);
} */