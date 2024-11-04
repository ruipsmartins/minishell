/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/04 15:01:45 by ruidos-s         ###   ########.fr       */
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

void	data_init(t_data *data, char **env)
{
	data->env = env;
	data->original_stdin = -1;
	data->original_stdout = -1;
	data->close_shell = false;
	data->return_value = 0;
}

// t_envvar_list	*init_env_list(void)
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

	data_init(&data, env);
	(void)ac;
	(void)av;
	input = get_command_input();
	while (input != NULL && !data.close_shell)
	{
		if (*input)
			handle_input(input, &data);
		if (data.close_shell)
			break ;
		free(input);
		// Debug return value of the command executed by the user (exit status)
		ft_printf("data.return_value na main: %d\n", data.return_value);
		input = get_command_input();
	}
	free(input);
	rl_clear_history();
	return (data.return_value);
}
