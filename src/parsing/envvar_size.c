/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 11:15:03 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/02 18:47:37 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_return(int return_value)
{
	int	size_of_nbm;

	size_of_nbm = 1;
	while (return_value / 10)
	{
		return_value /= 10;
		size_of_nbm++;
	}
	return (size_of_nbm);
}

size_t	calculate_final_len(const char *input, t_data *data)
{
	size_t		len;
	const char	*src;

	len = 0;
	src = input;
	while (*src)
	{
		if (*src == '$')
		{ 
			len += handle_variable(&src, data);
		}
		else
		{
			len++;
			src++;
		}
	}
	return (len);
}

char	*get_env_value(char *input)	//descobre o valor da variavel de ambiente
{
	int	i;
	int	k;

	i = 0;
	while (input[i] != '=' && input[i] != '\0')
		i++;
	k = i + 1;
	while (input[k] && input[k] != ' ')
		k++;
	return (ft_strndup (input + i + 1, k));
}

char	*get_env_name(char *input)	//descobre o nome da variavel de ambiente
{
	int	i;
	int	k;

	i = 0;
	while (input[i] != '=' && input[i] != '\0')
		i++;
	k = i - 1;
	if (!isalnum(input[i + 1]) || !isalnum(input[i - 1]))
	{
		printf("Invalid variable name\n");
		return (NULL);
	}
	while (k > 0 && input[k] && (isalnum(input[k - 1]) || input[k - 1] == '_'))
		k--;
	return (ft_strndup(input + k, i - k));
}
