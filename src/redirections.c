/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:11:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/09 14:13:32 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


void	handle_redirections(char **args)
{
	int		i = 0;
	int		in_file;
	int		out_file;

	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 1) == 0)
		{
			in_file = open(args[i + 1], O_RDONLY);
			if (in_file == -1)
			{
				perror("Failed to open input file");
				exit(EXIT_FAILURE);
			}
			dup2(in_file, STDIN_FILENO);
			close(in_file);
			args[i] = NULL;
		}
		else if (ft_strncmp(args[i], ">", 1) == 0)
		{
			out_file = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out_file == -1)
			{
				perror("Failed to open output file");
				exit(EXIT_FAILURE);
			}
			dup2(out_file, STDOUT_FILENO);
			close(out_file);
			args[i] = NULL;
		}
		i++;
	}
}