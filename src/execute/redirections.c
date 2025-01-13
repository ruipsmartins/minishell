/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:11:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/13 16:11:54 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_heredoc(t_command *cmd, int *original_stdin)
{
	int	heredoc_fd;

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
	return (0);
}

int	handle_input_redirect(t_command *cmd, int *original_stdin)
{
	int	in_file;

	if (cmd->heredoc && cmd->heredoc->heredoc == true)
		return (process_heredoc(cmd, original_stdin));
	else if (cmd->input_file && *cmd->input_file)
	{
		in_file = open(cmd->input_file, O_RDONLY);
		if (in_file == -1)
		{
			write(STDERR_FILENO, cmd->input_file, ft_strlen(cmd->input_file));
			write(STDERR_FILENO, ": Failed to open input file\n", 28);
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

	while (cmd->redirect && cmd->redirect->out_file)
	{
		if (cmd->append == true)
			out_file = open(cmd->redirect->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			out_file = open(cmd->redirect->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_file == -1)
		{
			write(STDERR_FILENO, cmd->redirect->out_file, ft_strlen(cmd->redirect->out_file));
			write(STDERR_FILENO, ": Failed to open output file\n", 29);
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
		cmd->redirect = cmd->redirect->next;
	}
	return (0);
}

int	handle_redirects(t_command *cmd, t_data *data)
{
	int	ret;

	ret = 0;
	if (handle_input_redirect(cmd, &data->original_stdin) == -1)
	{
		cleanup_child_data(data);
		if (g_var == 2)
			exit(130);
		exit(1);
	}
	if (ret == 0 && handle_output_redirect(cmd, &data->original_stdout) == -1)
	{
		cleanup_child_data(data);
		exit(1);
	}
	return (ret);
}
