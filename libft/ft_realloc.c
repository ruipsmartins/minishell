/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:54:22 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/06 15:28:13 by ruidos-s         ###   ########.fr       */
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
void *ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (ptr == NULL) {
        // Se ptr for NULL, comporta-se como malloc.
        return malloc(size);
    }
    if (size == 0) {
        // Se o tamanho for 0, liberta o bloco e retorna NULL.
        free(ptr);
        return NULL;
    }
    // Aloca um novo bloco de memória.
    new_ptr = malloc(size);
    if (!new_ptr) {
        // Retorna NULL se a alocação falhar.
        return NULL;
    }
    // Calcula o tamanho a copiar sem usar o operador ternário.
    copy_size = size; // Supondo inicialmente que `size` é o limite.
    // Aqui, usamos `memcpy` apenas até o tamanho disponível. 
    ft_memcpy(new_ptr, ptr, sizeof(ptr));
    // Liberta o bloco antigo.
    free(ptr);
    return new_ptr;
}
