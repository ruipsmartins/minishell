/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/22 12:56:07 by ruidos-s         ###   ########.fr       */
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
	t_data	data;

	data.env = env;
	data.original_stdin = -1;
	data.original_stdout = -1;
	data.close_shell = false;
	(void)ac;
	(void)av;
	input = get_command_input();
	while (input != NULL  && !data.close_shell)
	{
		if (*input)
			handle_input(input, &data);
		if (data.close_shell)
			break;
		free(input);
		input = get_command_input();
	}
	free(input);
	rl_clear_history();
	return (0);
}
