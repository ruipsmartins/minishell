/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:27:08 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/17 11:35:49 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	helper_output(t_command **current_cmd, t_redirect *new_redirect,
		t_lexer *current, bool append)
{
	t_redirect	*tmp;

	tmp = (*current_cmd)->redirect;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redirect;
	tmp->next->out_file = ft_strdup(current->word);
	tmp->next->append = append;
}

void	helper_heredoc(t_command **current_cmd, t_heredoc *new_heredoc,
		t_lexer *current)
{
	t_heredoc	*tmp;

	tmp = (*current_cmd)->heredoc;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_heredoc;
	tmp->next->heredoc = true;
	tmp->next->delimiter = ft_strdup(current->word);
}

void	helper_input(t_command **curent_cmd, t_input *new_input,
		t_lexer *current)
{
	t_input	*tmp;

	tmp = (*curent_cmd)->input;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_input;
	tmp->next->file_name = ft_strdup(current->word);
}

void	free_heredoc(t_command *current)
{
	t_heredoc	*tmp;

	while (current->heredoc)
	{
		free(current->heredoc->delimiter);
		if (current->heredoc->next)
		{
			tmp = current->heredoc->next;
			free(current->heredoc);
			current->heredoc = tmp;
		}
		else
		{
			free(current->heredoc);
			current->heredoc = NULL;
		}
	}
}

void	free_input(t_command *current)
{
	t_input	*tmp;

	while (current->input)
	{
		free(current->input->file_name);
		if (current->input->next)
		{
			tmp = current->input->next;
			free(current->input);
			current->input = tmp;
		}
		else
		{
			free(current->input);
			current->input = NULL;
		}
	}
}
