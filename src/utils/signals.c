/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/10 17:26:52 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c_parent(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = signal;
}

void	handle_here_doc_exit(int signal)
{
	g_var = signal;
	close(0);
}

void	ctrl_c_child(int signal)
{
	g_var = signal;
	write(1, "\n", 1);
}
