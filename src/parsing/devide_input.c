/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:07:57 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/17 18:03:53 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*create_new_node(t_quotes *quotes, int i, t_lexer *current)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (new_node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (is_token(quotes->token) && !(quotes->quotes))
		new_node->token = ft_strdup(quotes->token);
	else
		new_node->word = ft_strdup(quotes->token);
	new_node->i = i;
	new_node->prev = current;
	new_node->next = NULL;
	quotes->quotes = 0;
	return (new_node);
}

void	add_node_to_list(t_lexer **lexer, t_lexer *current, t_lexer *new_node)
{
	if (current != NULL)
		current->next = new_node;
	else
		*lexer = new_node;
}

t_lexer	*devide_input(char *input)
{
	t_lexer		*lexer;
	t_lexer		*current;
	int			i;
	t_lexer		*new_node;
	t_quotes	*quotes;

	quotes = (t_quotes *)ft_calloc(1, sizeof(t_quotes));
	quotes->quotes = 0;
	quotes->token = split_string(&input, quotes);
	lexer = NULL;
	current = NULL;
	i = 0;
	while (quotes->token != NULL)
	{
		new_node = create_new_node(quotes, i++, current);
		add_node_to_list(&lexer, current, new_node);
		current = new_node;
		free(quotes->token);
		quotes->token = split_string(&input, quotes);
	}
	free(quotes->token);
	free(quotes);
	return (lexer);
}
