/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/16 15:05:04 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_var;

char	*get_command_input(t_data *data)
{
	char	*input;

	input = readline("Minishell: ");
	if (input && *input)
	{
		input[ft_strlen(input)] = '\0';
		add_history(input);
	}
	if (g_var == 2)
	{
		g_var = 0;
		data->return_value = 130;
	}
	return (input);
}

void	data_init(t_data *data, char **env)
{
	signal(SIGINT, ctrl_c_parent);
	signal(SIGQUIT, SIG_IGN);
	data->env_var_lst = ft_create_env_list(env);
	data->env = swap_list_to_array(data->env_var_lst);
	data->original_stdin = -1;
	data->original_stdout = -1;
	data->close_shell = false;
	data->return_value = 0;
	data->cmd = NULL;
	data->executable = NULL;
}

int input_tester(char *input, t_data *data)
{
	if (*input && !only_spaces(input) && !check_4_pipe(input, data)
		&& !check_here_doc(input, data))
			return (1);
	else
		return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data, env);
	input = get_command_input(&data);
	while (input != NULL && !data.close_shell)
	{
		g_var = 0;
		if (input_tester(input, &data))
			handle_input(input, &data);
		if (data.close_shell)
			break ;
		input = get_command_input(&data);
	}
	cleanup_data(&data);
	return (data.return_value);
}
