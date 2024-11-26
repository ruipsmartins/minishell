/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/26 12:57:33 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_command_input(void)
{
	char	*input;

	input = readline("\033[32mMinishell:\033[0m ");
	if (input && *input)
		add_history(input);
	return (input);
}

void	data_init(t_data *data, char **env)
{
	data->env_var_lst = ft_create_env_list(env);
	data->env = swap_list_to_array(data->env_var_lst);
	data->original_stdin = -1;
	data->original_stdout = -1;
	data->close_shell = false;
	data->return_value = 0;
	data->cmd = NULL;
	data->fd[0] = -1;
	data->fd[1] = -1;
	
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

void free_data(t_data *data)
{
	int i;

	i = 0;
	while(data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	if(data->cmd)
		free_command_list(data->cmd);
	//if(data->env_var_lst)
		//free_env_list(data->env_var_lst);
	//free(data);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data, env);
	
	input = get_command_input();
	(void)data;
	while (input != NULL  && !data.close_shell)
	{
		if (*input)
			handle_input(input, &data);
		if (data.close_shell)
			break ;
		// Debug return value of the command executed by the user (exit status)
		//ft_printf("data.return_value na main: %d\n", data.return_value);
		free_command_list(data.cmd);
	
		input = get_command_input();
		// int i = 0;									//para teste
		// while(env_list_array[i])						//para teste
		// {											//para teste						
		// 	printf("%s\n", env_list_array[i]);		//para teste
		// 	i++;									//para teste
		// }
	}
		if (data.env_var_lst)
			free_env_list(data.env_var_lst);
	free_data(&data);
	rl_clear_history();
	return (data.return_value);
}
