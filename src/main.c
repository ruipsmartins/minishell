/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/19 12:46:21 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command_input(void)
{
	char	*input;

	input = readline("Minishell: ");
	if (input && *input)
		add_history(input);
	return (input);
}

// t_envvar_list	*init_env_list()
// {
// 	t_envvar_list	*env_list;

// 	env_list = (t_envvar_list *)ft_calloc(1, sizeof(t_envvar_list));
// 	if (env_list == NULL)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	env_list->head = NULL;
// 	return (env_list);
// }

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	input = get_command_input();
	while (input != NULL)
	{
		if (*input)
			handle_input(input, env);
		free(input);
		input = get_command_input();
	}
	free(input);
	rl_clear_history();
	return (0);
}
