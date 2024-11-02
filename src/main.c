/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/02 14:40:45 by addicted         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;


	t_envvar *env_list;
	data.env = env;
	data.original_stdin = -1;
	data.original_stdout = -1;
	data.close_shell = false;
	(void)ac;
	(void)av;
	
	env_list = ft_create_list(env);
	//print_list(env_list);
	input = get_command_input();

	(void)data;
	while (input != NULL  && !data.close_shell)
	{
		if (*input)

			handle_input(input, &data, env_list);
		if (data.close_shell)
			break;
		free(input);
		input = get_command_input();
	}
	free(input);
	rl_clear_history();
	return (0);
}
