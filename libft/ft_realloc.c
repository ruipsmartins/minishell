/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:54:22 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/06 16:59:35 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* The  realloc()  function  changes the size of the memory block pointed
to by ptr to size bytes.  The contents will be unchanged in the range from
the start of the region up to the minimum of the old and new sizes.  If the
new size is larger than the old size, the added memory will not be initialized.
If ptr is NULL, then the call is equivalent to malloc(size),
for all values of size; if size is equal to zero, and ptr is not NULL, then the
call is equivalent to free(ptr).  Unless ptr is NULL, it must have been
returned by an earlier call to malloc(), calloc(), or realloc().
If the area pointed to was moved, a free(ptr) is done. */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}
