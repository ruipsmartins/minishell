/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:01:43 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/16 14:11:41 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int execute_heredoc(t_command *cmd)
{
    int     pipe_fd[2];
    char    *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");  // Lê input do utilizador
        if (!line || strcmp(line, cmd->delimiter) == 0) // Verifica se atingiste o delimitador
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, strlen(line));  // Escreve a linha no pipe
        write(pipe_fd[1], "\n", 1);  // Adiciona nova linha após cada input
        free(line);
    }
    close(pipe_fd[1]);  // Fecha o lado de escrita do pipe

    return (pipe_fd[0]);  // Retorna o lado de leitura do pipe para redirecionar o stdin
}