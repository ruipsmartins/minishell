/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:11:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/16 14:57:23 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Restaurar o stds se foram alterados
/* void	std_reset(int *original_stdin, int *original_stdout)
{
	if (*original_stdin != -1)
	{
		dup2(*original_stdin, STDIN_FILENO);
		close(*original_stdin);
	}
	if (*original_stdout != -1)
	{
		dup2(*original_stdout, STDOUT_FILENO);
		close(*original_stdout);
	}
} */

int	handle_input_redirect(t_command *cmd, int *original_stdin)
{
	int	in_file;
	int	heredoc_fd;

	if (cmd->heredoc == true)
	{
		*original_stdin = dup(STDIN_FILENO);
		if (*original_stdin == -1)
			return (-1);
		heredoc_fd = execute_heredoc(cmd);
		if (heredoc_fd == -1)
		{
			close(*original_stdin);
			return (-1);
		}
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	else if (cmd->input_file && *cmd->input_file)
	{
		in_file = open(cmd->input_file, O_RDONLY);
		if (in_file == -1)
		{
			ft_printf("%s: Failed to open input file\n", cmd->input_file);
			return (-1);
		}
		*original_stdin = dup(STDIN_FILENO);
		if (*original_stdin == -1)
		{
			ft_printf("Failed to duplicate stdin\n");
			close(in_file);
			return (-1);
		}
		dup2(in_file, STDIN_FILENO);
		close(in_file);
	}
	return (0);
}

int	handle_output_redirect(t_command *cmd, int *original_stdout)
{
	int	out_file;

	if (cmd->output_file && *cmd->output_file)
	{
		if (cmd->append == true)
			out_file = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			out_file = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (out_file == -1)
		{
			ft_printf("%s: Failed to open output file\n", cmd->output_file);
			return (-1);
		}
		*original_stdout = dup(STDOUT_FILENO);
		if (*original_stdout == -1)
		{
			ft_printf("Failed to duplicate stdout\n");
			close(out_file);
			return (-1);
		}
		dup2(out_file, STDOUT_FILENO);
		close(out_file);
	}
	return (0);
}

int	handle_redirects(t_command *cmd, t_data *data)
{
	int ret;

	ret= 0;
	if (handle_input_redirect(cmd, &data->original_stdin) == -1)
		ret= -1;
	if (handle_output_redirect(cmd, &data->original_stdout) == -1)
		ret= -1;
	if (global_var == 130)
	{
		signal(SIGINT, ctrl_c_parent);
		global_var = 0;
		exit(130);
	}
	return (ret);
}
