/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:32:09 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/13 14:43:39 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_pipe_token(t_command **current_cmd, int *arg_count)
{
	(*current_cmd)->next = (t_command *)ft_calloc(1, sizeof(t_command));
	*current_cmd = (*current_cmd)->next;
	*arg_count = 0;
}

t_lexer	*handle_append(t_lexer *current, t_command **current_cmd,
t_command **cmd_list)
{
	current = current->next;
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		(*current_cmd)->append = true;

		t_redirect *new_redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if ((*current_cmd)->redirect == NULL)
		{
			(*current_cmd)->redirect = new_redirect;
			(*current_cmd)->redirect->out_file = ft_strdup(current->word);
			(*current_cmd)->redirect->append = true;
		}
		else
		{
			t_redirect *tmp = (*current_cmd)->redirect;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_redirect;
			tmp->next->out_file = ft_strdup(current->word);
			tmp->next->append = true;
		}
	return (current);
}

t_lexer	*handle_heredoc(t_lexer *current, t_command **current_cmd,
t_command **cmd_list)
{
	current = current->next;
	if (current && current->word)
	{
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		(*current_cmd)->heredoc = true;
		(*current_cmd)->delimiter = ft_strdup(current->word);
	}
	return (current);
}

t_lexer	*handle_output_redirection(t_lexer *current,
t_command **current_cmd, t_command **cmd_list)
{
	current = current->next;
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		(*current_cmd)->append = false;
		t_redirect *new_redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
		if ((*current_cmd)->redirect == NULL)
		{
			(*current_cmd)->redirect = new_redirect;
			(*current_cmd)->redirect->out_file = ft_strdup(current->word);
			(*current_cmd)->redirect->append = false;
		}
		else
		{
			t_redirect *tmp = (*current_cmd)->redirect;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new_redirect;
			tmp->next->out_file = ft_strdup(current->word);
			tmp->next->append = false;
		}
	return (current);
}

t_lexer	*handle_input_redirection(t_lexer *current,
t_command **current_cmd, t_command **cmd_list)
{
	current = current->next;
	if (current && current->word)
	{
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		(*current_cmd)->input_file = ft_strdup(current->word);
	}
	return (current);
}
