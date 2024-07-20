/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/07/20 14:02:33 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>



int main() {
    // Define um prompt para o utilizador
    const char* prompt = "Introduz uma linha: ";

    // Usa readline para obter uma linha de input do utilizador
    char* input = readline(prompt);

    if (input != NULL) {
        // A linha de input é retornada alocada com malloc, então precisamos libertá-la depois de a usar
        printf("Leste: %s\n", input);
        free(input);
    } else {
        printf("Erro ao ler a linha ou linha vazia.\n");
    }

    return 0;
}