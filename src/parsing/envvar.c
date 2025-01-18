/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2025/01/18 20:27:47 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_new_envvar(t_envvar **env_list, char *name, char *value)
{
	t_envvar	*new_node;

	new_node = (t_envvar *)ft_calloc(1, sizeof(t_envvar));
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	ft_envadd_back(env_list, new_node);
}

// vai buscar o ultimo elemento da lista
t_envvar	*ft_last_env(t_envvar *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

// addicona um novo elemento no fim da lista
void	ft_envadd_back(t_envvar **lst, t_envvar *new)
{
	t_envvar	*current;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = ft_last_env(*lst);
	current->next = new;
}

t_envvar	*find_envvar(t_envvar *lst, char *name)
{
	t_envvar	*current;

	if (lst == NULL || name == NULL)
		return (NULL);
	current = lst;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name) + 1) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

// criar uma nova lista de variaveis de ambiente com o ENV
t_envvar	*ft_create_env_list(char **env)
{
	char		**current;
	t_envvar	*new_node;
	t_envvar	*head;

	head = NULL;
	if (*(env) == NULL )
	{
		head = no_env(head);
		return (head);
	}
	current = env;
	while (*current)
	{
		new_node = (t_envvar *)ft_calloc(1, sizeof(t_envvar));
		new_node->name = ft_strndup(*current, ft_strchr(*current, '=')
				- *current);
		new_node->value = ft_strdup(ft_strchr(*current, '=') + 1);
		ft_envadd_back(&head, new_node);
		current++;
	}
	set_shlvl(head);
	return (head);
}
