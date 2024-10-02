/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:11:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/26 17:48:16 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"


int handle_redirects(t_command *cmd, int *original_stdin, int *original_stdout)
{
	// Redirecionamento de input, se houver
	if (cmd->input_file && *cmd->input_file)
	{
		int in_file = open(cmd->input_file, O_RDONLY);
		if (in_file == -1)
		{
			ft_printf("%s: Failed to open input file\n", cmd->input_file);
			return (-1);
		}
		*original_stdin = dup(STDIN_FILENO);  // Salva o stdin original
		if (*original_stdin == -1)
		{
			ft_printf("Failed to duplicate stdin\n");
			close(in_file);
			return (-1);
		}
		dup2(in_file, STDIN_FILENO);          // Redireciona input para o ficheiro
		close(in_file);
	}

	// Redirecionamento de output, se houver
	if (cmd->output_file && *cmd->output_file)
	{
		int out_file = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_file == -1)
		{
			ft_printf("%s: Failed to open output file\n", cmd->output_file);
			return (-1);
		}
		*original_stdout = dup(STDOUT_FILENO);  // Salva o stdout original
		if (*original_stdout == -1)
		{
			ft_printf("Failed to duplicate stdout\n");
			close(out_file);
			return (-1);
		}
		dup2(out_file, STDOUT_FILENO);           // Redireciona output para o ficheiro
		close(out_file);
	}

	return (0);
}
