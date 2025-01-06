/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:54:22 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/06 13:55:15 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void *ft_realloc(void *ptr, size_t old_size, size_t new_size) {
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    void *new_ptr = malloc(new_size);
    if (!new_ptr)
        return NULL; // Retorna NULL se não houver memória suficiente.

    if (ptr) {
        // Copia os dados do bloco antigo para o novo (o máximo entre os dois tamanhos).
        size_t copy_size = (old_size < new_size) ? old_size : new_size;
        memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }

    return new_ptr;
}
