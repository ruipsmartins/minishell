/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:17:42 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/17 11:35:12 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_envvar *env_list)
{
	t_envvar	*current;
	t_envvar	*next;

	current = env_list;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_redirect(t_command *current)
{
	t_redirect	*tmp;

	if (current->redirect)
	{
		while (current->redirect)
		{
			free(current->redirect->out_file);
			if (current->redirect->next)
			{
				tmp = current->redirect->next;
				free(current->redirect);
				current->redirect = tmp;
			}
			else
			{
				free(current->redirect);
				current->redirect = NULL;
			}
		}
	}
}

void	free_command_list(t_command *cmd_list) // free da lista de comandos
{
	int			i;
	t_command	*current;
	t_command	*next;

	current = cmd_list;
	while (current != NULL)
	{
		next = current->next;
		if (current->args)
		{
			i = 0;
			while (current->args[i] != NULL)
				free(current->args[i++]);
			free(current->args);
		}
		free_heredoc(current);
		free_redirect(current);
		free_input(current);
		free(current);
		current = next;
	}
}

void	free_lexer(t_lexer *lexer)
{
	t_lexer	*current;
	t_lexer	*next;

	current = lexer;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		free(current->word);
		free(current->token);
		current->next = NULL;
		free(current);
		current = next;
	}
}
