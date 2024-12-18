/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:56 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/18 12:24:17 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	ctrl_c_parent(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = 130;
	(void)signal;
}
void	handle_here_doc_exit(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_var = 130;
	close(0);
}

void	ctrl_c_child(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	g_var = 130;
}


