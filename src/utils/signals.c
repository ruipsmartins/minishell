/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/11 18:33:26 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"


void sigint_handler(int signum)
{
    //(void)signum;
	signal_received = signum; 
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/* void sigquit_handler(int signum) {
    (void)signum; // Ignorar o argumento
    // Não faz nada
} */

void setup_signals(void)
{
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