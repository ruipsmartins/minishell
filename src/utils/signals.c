/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/11 16:10:51 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


void sigint_handler(int signum) {
    (void)signum; // Ignorar o argumento
    write(1, "\n", 1); // Escreve uma nova linha
    rl_on_new_line(); // Informa o readline que estamos numa nova linha
    rl_replace_line("", 0); // Limpa o input atual
    rl_redisplay(); // Mostra um novo prompt
}

void sigquit_handler(int signum) {
    (void)signum; // Ignorar o argumento
    // Não faz nada
}

void setup_signals(void) {
    struct sigaction sa;

    // SIGINT (Ctrl-C)
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Reinicia funções bloqueantes como read/write
    sigaction(SIGINT, &sa, NULL);

    // SIGQUIT (Ctrl-\)
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, NULL);
}