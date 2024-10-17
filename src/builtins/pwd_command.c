/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:21:15 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/17 17:42:10 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_command(void)
{
	char *buffer;

	buffer = getcwd(NULL, 0);
	if (!buffer)
	{
		perror("getcwd:");
		return ;
	}

	ft_printf("%s\n", buffer);
	free(buffer);
}
