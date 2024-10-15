/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:50:11 by addicted          #+#    #+#             */
/*   Updated: 2024/10/15 19:13:31 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_pipe_token(t_command **current_cmd, int *arg_count)
{
	(*current_cmd)->next = (t_command *)ft_calloc(1, sizeof(t_command));
	*current_cmd = (*current_cmd)->next;
	*arg_count = 0;
}

t_lexer *handle_append(t_lexer *current, t_command **current_cmd, t_command **cmd_list)
{
	current = current->next;
	if (current && current->word)
	{
		if (*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		(*current_cmd)->append = true;
		(*current_cmd)->output_file = ft_strdup(current->word);
	}
	return (current);
}
t_lexer *handle_heredoc(t_lexer *current, t_command **current_cmd, t_command **cmd_list)
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
		(*current_cmd)->heredoc_last_wd = ft_strdup(current->word);// guardar a ultima palavra do heredoc
	}
	return current;
}

t_lexer	*handle_output_redirection(t_lexer *current, t_command **current_cmd, t_command **cmd_list)
{
	current = current->next;
	if (current && current->word)
	{
		if(*current_cmd == NULL)
		{
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
			*cmd_list = *current_cmd;
		}
		(*current_cmd)->append = false;
		(*current_cmd)->output_file = ft_strdup(current->word);
	}
	return (current);
}

t_lexer	*handle_input_redirection(t_lexer *current, t_command **current_cmd, t_command **cmd_list)
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

void handle_argument(t_lexer *current, t_command **current_cmd, t_command **cmd_list, int *arg_count)
{
	if(*arg_count == 0)
	{
		if(*cmd_list == NULL)
		{
			*cmd_list = (t_command *)ft_calloc(1, sizeof(t_command));
			*current_cmd = *cmd_list;
		}
		else if (*current_cmd == NULL)
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	}
	(*current_cmd)->args = (char **)realloc((*current_cmd)->args, sizeof(char *) * (*arg_count + 2));
	(*current_cmd)->args[*arg_count] = ft_strdup(current->word);
	(*current_cmd)->args[*arg_count + 1] = NULL;
	(*arg_count)++;
}
t_command *lexer_to_command(t_lexer *lexer)
{
	t_command *cmd_list = NULL;
	t_command *current_cmd = NULL;
	t_lexer *current = lexer;
	int arg_count = 0;

	while (current != NULL)
	{
		if (current->token && strncmp(current->token, "|", 2) == 0)
			handle_pipe_token(&current_cmd, &arg_count);
		else if (current->token && strncmp(current->token, ">>", 3) == 0) //
			current =  handle_append(current, &current_cmd, &cmd_list);
		else if (current->token && strncmp(current->token, ">", 2) == 0) //
			current = handle_output_redirection(current, &current_cmd, &cmd_list);
		else if (current->token && strncmp(current->token, "<<", 3) == 0) //
			current = handle_heredoc(current, &current_cmd, &cmd_list);
		else if (current->token && strncmp(current->token, "<", 2) == 0) //
			current = handle_input_redirection(current, &current_cmd, &cmd_list);
		else
			handle_argument(current, &current_cmd, &cmd_list, &arg_count);
		current = current->next;
	}
	return cmd_list;
}
