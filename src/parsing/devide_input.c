/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:07:57 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/17 16:24:11 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*create_new_node(char *token, int i, t_lexer *current, int *quotes)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (new_node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (is_token(token) && !(*quotes))
		new_node->token = ft_strdup(token);
	else
		new_node->word = ft_strdup(token);
	new_node->i = i;
	new_node->prev = current;
	new_node->next = NULL;
	
	*quotes = 0;
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
	t_lexer	*lexer;
	t_lexer	*current;
	char	*token;
	int		i;
	t_lexer	*new_node;
	int		was_in_quotes;
	
	was_in_quotes = 0;
	token = split_string(&input, &was_in_quotes);
	lexer = NULL;
	current = NULL;
	i = 0;
	while (token != NULL)
	{
		new_node = create_new_node(token, i++, current, &was_in_quotes);
		add_node_to_list(&lexer, current, new_node);
		current = new_node;
		free(token);
		token = split_string(&input, &was_in_quotes);
	}
	free(token);
	return (lexer);
}
