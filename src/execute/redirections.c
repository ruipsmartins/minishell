/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:11:52 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/15 16:00:24 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_file_error(char *str1, char *str2, int file, int returnCode)
{
	if (file == -1)
	{
		if (str1)
			write(STDERR_FILENO, str1, ft_strlen(str1));
		if (str2)
			write(STDERR_FILENO, str2, ft_strlen(str2));
		return (returnCode);
	}
	else
	{
		write(STDERR_FILENO, str2, ft_strlen(str2));
		close(file);
	}
	return (returnCode);
}

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
	int		in_fd;
	char	*input_file_name;

	

	if (cmd->heredoc && cmd->heredoc->heredoc == true)
		return (process_heredoc(cmd, original_stdin));
	while(cmd->input && cmd->input->file_name)
	{
		if (cmd->input->file_name && *cmd->input->file_name)
		{
			input_file_name = cmd->input->file_name;
			in_fd = open(cmd->input->file_name, O_RDONLY);
			if (in_fd == -1)
				return (handle_file_error(input_file_name,
						": Failed to open input file\n", in_fd, -1));
			*original_stdin = dup(STDIN_FILENO);
			if (*original_stdin == -1)
				return (handle_file_error(NULL, "Failed to duplicate stdin\n",
						in_fd, -1));
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		cmd->input = cmd->input->next;
	}
	return (0);
}

int	handle_output_redirect(t_command *cmd, int *original_stdout)
{
	int		out_fd;
	char	*out_file_name;

	while (cmd->redirect && cmd->redirect->out_file)
	{
		out_file_name = cmd->redirect->out_file;
		if (cmd->redirect->append == true)
			out_fd = open(out_file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			out_fd = open(out_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
			return (handle_file_error(cmd->redirect->out_file,
					": Failed to open output file\n", out_fd, -1));
		*original_stdout = dup(STDOUT_FILENO);
		if (*original_stdout == -1)
			return (handle_file_error(NULL, "Failed to duplicate stdout\n",
					out_fd, -1));
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
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
