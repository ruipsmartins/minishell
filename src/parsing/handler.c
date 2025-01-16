/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:32:09 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/16 00:05:11 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_pipe_token(t_command **current_cmd, int *arg_count)
{
	(*current_cmd)->next = (t_command *)ft_calloc(1, sizeof(t_command));
	*current_cmd = (*current_cmd)->next;
	*arg_count = 0;
}

t_lexer	*handle_heredoc(t_lexer *current, t_command **current_cmd,
t_command **cmd_list)
{
	t_heredoc *new_heredoc;

	current = current->next;
	if (current && current->word)
	{
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		new_heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
		if ((*current_cmd)->heredoc == NULL)
		{
			(*current_cmd)->heredoc = new_heredoc;
			if ((*current_cmd)->heredoc)
				(*current_cmd)->heredoc->delimiter = ft_strdup(current->word);
			(*current_cmd)->heredoc->heredoc = true;
		}
		else
			helper_heredoc(current_cmd, new_heredoc, current);
	}
	return (current);
}

t_lexer	*handle_output(t_lexer *current,
t_command **current_cmd, t_command **cmd_list, bool append)
{
	t_redirect *new_redirect;

	current = current->next;
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		new_redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if ((*current_cmd)->redirect == NULL)
		{
			(*current_cmd)->redirect = new_redirect;
			(*current_cmd)->redirect->out_file = ft_strdup(current->word);
			(*current_cmd)->redirect->append = append;
		}
		else
			helper_output(current_cmd, new_redirect, current, append);
	return (current);
}

t_lexer	*handle_input_redirection(t_lexer *current,
t_command **current_cmd, t_command **cmd_list)
{
	t_input *new_input;
	
	//if(current->next)
		current = current->next;
	//current = current->next;
	if (current && current->word)
	{
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		new_input = (t_input*)ft_calloc(1, sizeof(t_input));
		if ((*current_cmd)->input == NULL)
		{
			(*current_cmd)->input = new_input;
			(*current_cmd)->input->file_name = ft_strdup(current->word);
		}
		else
			helper_input(current_cmd, new_input, current);
	}
	return (current);
}
