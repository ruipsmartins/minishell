/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/30 18:47:18 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_var;

char	*get_command_input(t_data *data)
{
	char	*input;

	input = readline("\033[32mMinishell:\033[0m ");
	if (input && *input)
	{
		input[ft_strlen(input)] = '\0';
		add_history(input);
	}
	if (g_var == 130)
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

int	only_spaces(char *input)
{
	while (*input)
	{
		if (!isspace(*input))
			return (0);
		input++;
	}
	return (1);
}

int	check_4_pipe(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '\0')
			{
				data->return_value = 2;
				return (ft_printf("\033[32mMinishell:\033[0m  syntax error near unexpected token `|'\n"));
			}
		}
		if (input[i] != '\0')
			i++;
	}
	return (0);
}

int	check_here_doc(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] != '<' && input[i] != '\0')
		i++;
	if (input[i] == '<' && input[i + 1] == '<')
	{
		i += 2;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0' || input[i] == '|')
		{
			data->return_value = 2;
			return (ft_printf("\033[32mMinishell:\033[0m  syntax error near unexpected token `<<'\n"));
		}
		else
			return (0);
	}
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
		if (*input && !only_spaces(input) && !check_4_pipe(input, &data)
			&& !check_here_doc(input, &data))
			handle_input(input, &data);
		if (data.close_shell)
			break ;
		if (!input && !only_spaces(input))
			free_command_list(data.cmd);
		input = get_command_input(&data);
	}
	if (data.env_var_lst)
		free_env_list(data.env_var_lst);
	cleanup_data(&data);
	rl_clear_history();
	return (data.return_value);
}
