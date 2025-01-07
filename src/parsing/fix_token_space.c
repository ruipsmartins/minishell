/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:43 by addicted          #+#    #+#             */
/*   Updated: 2025/01/07 14:55:13 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_token(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i++])
	{
		if (check_if_token(str[i]))
		{
			c = str[i];
			if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
				i++;
			while (str[i + 1] == ' ')
				i++;
			if (c != '|')
			{
				if (check_if_token(str[i + 1]))
					return (ft_printf("Syntax error near `%c'\n", str[i + 1]));
				if (str[i + 1] == '\0')
					return (ft_printf("Syntax error near `%c'\n", c));
			}
			if (str[i + 1] == '|')
				return (ft_printf("Syntax error near `%c'\n", str[i +1]));
		}
	}
	return (0);
}

void	token_space(char *str, int i, int k, char *fix_str)
{
	while (str[i])
	{
		if (check_if_token(str[i]))
		{
			fix_str[k++] = ' ';
			fix_str[k] = str[i];
			if (str[i + 1] == str[i])
			{
				fix_str[++k] = str[++i];
				fix_str[++k] = ' ';
			}
			else if (str[i + 1] != str[i] && str[i + 1])
				fix_str[++k] = ' ';
		}
		else
			fix_str[k] = str[i];
		k++;
		i++;
	}
	fix_str[k] = '\0';
}

char	*fix_token_space(char *str, t_data *data)
{
	int		i;
	int		k;
	char	*fix_str;

	i = 0;
	k = 0;
	if (check_token(str))
	{
		data->return_value = 2;
		free(str);
		return (NULL);
	}
	fix_str = malloc(ft_strlen(str) + (count_token(str) * 2) + 1);
	token_space(str, i, k, fix_str);
	free(str);
	return (fix_str);
}
