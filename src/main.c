/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/11/06 12:06:53 by addicted         ###   ########.fr       */
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
char	**swap_list_to_array(t_envvar *env_list)
{
	t_envvar *current;
	int i;
	char **env;
	
	i = 0;
	current = env_list;
	while(current != NULL)
	{
		current = current->next;
		i++;
	}
	current = env_list;
	env = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (current != NULL)
	{
		env[i] = ft_strjoin(current->name, "=");
		env[i] = ft_strjoin(env[i], current->value);
		current = current->next;
		i++;
	}
	env[i] = NULL;
	return (env);
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
	
	env_list = ft_create_env_list(env);
	data.env_var_lst = env_list;     //passar a lista de variaveis de ambiente para a struct data
	
	
	//char **env_list_array;							//para teste
	//env_list_array = swap_list_to_array(env_list); //para teste
	
	input = get_command_input();
	(void)data;
	while (input != NULL  && !data.close_shell)
	{
		if (*input)
			handle_input(input, &data);
		if (data.close_shell)
			break ;
		free(input);
		// Debug return value of the command executed by the user (exit status)
		ft_printf("data.return_value na main: %d\n", data.return_value);
		input = get_command_input();
		// int i = 0;									//para teste
		// while(env_list_array[i])						//para teste
		// {											//para teste						
		// 	printf("%s\n", env_list_array[i]);		//para teste
		// 	i++;									//para teste
		// }											//para teste
	}
	free(input);
	rl_clear_history();
	return (data.return_value);
}
