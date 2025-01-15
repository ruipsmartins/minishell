/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_to_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:50:11 by addicted          #+#    #+#             */
/*   Updated: 2025/01/15 13:43:33 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_pipe_token(t_command **current_cmd, int *arg_count)
// {
// 	(*current_cmd)->next = (t_command *)ft_calloc(1, sizeof(t_command));
// 	*current_cmd = (*current_cmd)->next;
// 	*arg_count = 0;
// }

// t_lexer	*handle_append(t_lexer *current, t_command **current_cmd,
// t_command **cmd_list)
// {
// 	current = current->next;
// 	if (current && current->word)
// 	{
// 		if (*current_cmd == NULL)
// 		{
// 			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
// 			*cmd_list = *current_cmd;
// 		}
// 		(*current_cmd)->append = true;
// 		(*current_cmd)->out_file = ft_strdup(current->word);
// 	}
// 	return (current);
// }

// t_lexer	*handle_heredoc(t_lexer *current, t_command **current_cmd,
// t_command **cmd_list)
// {
// 	current = current->next;
// 	if (current && current->word)
// 	{
// 		if (*current_cmd == NULL)
// 		{
// 			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
// 			*cmd_list = *current_cmd;
// 		}
// 		(*current_cmd)->heredoc = true;
// 		(*current_cmd)->delimiter = ft_strdup(current->word);
// 	}
// 	return (current);
// }

// t_lexer	*handle_output_redirection(t_lexer *current,
// t_command **current_cmd, t_command **cmd_list)
// {
// 	current = current->next;
// 	if (current && current->word)
// 	{
// 		if (*current_cmd == NULL)
// 		{
// 			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
// 			*cmd_list = *current_cmd;
// 		}
// 		(*current_cmd)->append = false;
// 		(*current_cmd)->out_file = ft_strdup(current->word);
// 	}
// 	return (current);
// }

// t_lexer	*handle_input_redirection(t_lexer *current,
// t_command **current_cmd, t_command **cmd_list)
// {
// 	current = current->next;
// 	if (current && current->word)
// 	{
// 		if (*current_cmd == NULL)
// 		{
// 			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
// 			*cmd_list = *current_cmd;
// 		}
// 		(*current_cmd)->input_file = ft_strdup(current->word);
// 	}
// 	return (current);
// }

void	handle_argument(t_lexer *current,
	t_command **current_cmd, t_command **cmd_list, int *arg_count)
{
	static size_t	args_size = 0;
	size_t			new_size;

	if (*arg_count == 0)
	{
		if (*cmd_list == NULL)
		{
			*cmd_list = (t_command *)ft_calloc(1, sizeof(t_command));
			*current_cmd = *cmd_list;
		}
		else if (*current_cmd == NULL)
			*current_cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	}
	new_size = sizeof(char *) * (*arg_count + 2);
	(*current_cmd)->args = (char **)ft_realloc((*current_cmd)->args,
			args_size, new_size);
	args_size = new_size;
	(*current_cmd)->args[*arg_count] = ft_strdup(current->word);
	(*current_cmd)->args[*arg_count + 1] = NULL;
	(*arg_count)++;
}

int	is_null_token(t_lexer *current)
{
	if (current->word == NULL && current->token == NULL)
	{
		printf("Error: Both word and token are NULL\n");
		return (1);
	}
	return (0);
}

// Process the current token and decide which handler to call
t_lexer	*handle_token(t_lexer *current, t_command **current_cmd,
t_command **cmd_list, int *arg_count)
{
	if (current->token && ft_strncmp(current->token, "|", 2) == 0)
		handle_pipe_token(current_cmd, arg_count);
	else if (current->token && ft_strncmp(current->token, ">>", 3) == 0)
		current = handle_output(current, current_cmd, cmd_list, true);
	else if (current->token && ft_strncmp(current->token, ">", 2) == 0)
		current = handle_output(current, current_cmd, cmd_list, false);
	else if (current->token && ft_strncmp(current->token, "<<", 3) == 0)
		current = handle_heredoc(current, current_cmd, cmd_list);
	else if (current->token && ft_strncmp(current->token, "<", 2) == 0)
		current = handle_input_redirection(current, current_cmd, cmd_list);
	else
		handle_argument(current, current_cmd, cmd_list, arg_count);
	return (current->next);
}

t_command	*lexer_to_command(t_lexer *lexer)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_lexer		*current;
	int			arg_count;

	cmd_list = NULL;
	current_cmd = NULL;
	current = lexer;
	arg_count = 0;
	while (current != NULL)
	{
		if (is_null_token(current))
		{
			current = current->next;
			continue ;
		}
		current = handle_token(current, &current_cmd, &cmd_list, &arg_count);
	}
	return (cmd_list);
}
