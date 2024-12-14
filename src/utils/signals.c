/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/14 14:28:06 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	ctrl_c_parent(int signal)
{
	write(1, "\n", 1);
    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	global_var = 130;
	(void)signal;
}
void	quit_here_doc(int signal)
{
	close(0);
	global_var = 130;
	(void)signal;
}

void	ctrl_c_child(int signal)
{
	write(1, "\n", 1);
	global_var = 130;
	(void)signal;
}

void	ctrl_c_signal_hd(int signal)
{
	global_var = 130;
	(void)signal;
}

