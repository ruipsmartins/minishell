/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devide_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 17:07:57 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/06 12:37:35 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*create_new_node(char *token, int i, t_lexer *current)
{
	t_lexer	*new_node;

	new_node = (t_lexer *)ft_calloc(1, sizeof(t_lexer));
	if (new_node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (is_token(token))
		new_node->token = ft_strdup(token);
	else
		new_node->word = ft_strdup(token);
	new_node->i = i;
	new_node->prev = current;
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

	token = split_string(&input);
	lexer = NULL;
	current = NULL;
	i = 0;
	while (token != NULL)
	{
		new_node = create_new_node(token, i++, current);
		add_node_to_list(&lexer, current, new_node);
		current = new_node;
		free(token);
		token = split_string(&input);
	}
	free(token);
	return (lexer);
}
