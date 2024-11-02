/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 12:05:41 by addicted          #+#    #+#             */
/*   Updated: 2024/11/01 14:06:10 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envvar *ft_envlast(t_envvar *lst)
{
	while(lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void ft_envadd_back(t_envvar **lst, t_envvar *new)
{
	t_envvar *current;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	current = ft_envlast(*lst);
	current->next = new;
}

void	print_list(t_envvar *env_list)
{
	t_envvar *current;

	current = env_list;
	printf("Printing list\n");
	while (current != NULL)
	{
		printf("name:%s  =  %s(value)\n", current->name, current->value);
		
		current = current->next;
	}
}

t_envvar	*ft_get_envvar(t_envvar *lst, char *name)
{
	t_envvar *current;
	
	if(lst == NULL || name == NULL)
		return (NULL);
	current = lst;
	while(current)
	{
		//printf("name = %s\n", current->name);
		if (strcmp(current->name, name) == 0)  // strcmp tem de passar para ft_strcmp mas nao esta feito
			return (current);
		current = current->next;
	}
	printf("Deu bosta\n");
	return (NULL);
}

t_envvar *ft_create_list(char **env)
{
	char 		**current;
	t_envvar	 *new_node;
	t_envvar	 *head;

	head = NULL;
	current = env;
	while(*current)
	{
		new_node = (t_envvar *)ft_calloc(1, sizeof(t_envvar));
		//new_node->name = ft_strdup(*current);
		new_node->name = strndup(*current, ft_strchr(*current, '=') - *current);  // passar para ft_strndup
		new_node->value = ft_strdup(ft_strchr(*current, '=') + 1);
		ft_envadd_back(&head, new_node);
		current++;
	}
	return (head);
}

