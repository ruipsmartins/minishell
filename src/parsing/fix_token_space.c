/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:43 by addicted          #+#    #+#             */
/*   Updated: 2025/01/18 11:15:09 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_token_error(char *str, char c, int i)
{
	if (c != '|')
	{
		if (check_if_token(str[i]) && !in_quotes_check(str, i))
		{
			ft_putstr_fd("Syntax error near ", 2);
			ft_putchar_fd(str[i], 2);
			return (write(2, "\n", 1));
		}
		if (str[i + 1] == '\0')
		{
			ft_putstr_fd("Syntax error near ", 2);
			ft_putchar_fd(c, 2);
			return (write(2, "\n", 1));
		}
	}
	if (str[i + 1] == '|' && !in_quotes_check(str, i))
	{
		ft_putstr_fd("Syntax error near ", 2);
		ft_putchar_fd(str[i + 1], 2);
		return (write(2, "\n", 1));
	}
	return (0);
}

int	check_token(char *str)
{
	int		i;
	char	c;
	bool	quotes;

	quotes = false;
	i = 0;
	while (str[i])
	{
		if (check_if_token(str[i]) && !quotes)
		{
			c = str[i];
			if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
				i++;
			while (ft_isspace(str[i + 1]))
				i++;
			if (check_token_error(str, c, i))
				return (1);
		}
		i++;
	}
	return (0);
}

void	token_space(char *str, int i, int k, char *fix_str)
{
	while (str[i])
	{
		if (check_if_token(str[i]) && !in_quotes_check(str, i))
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
	fix_str = malloc(ft_strlen(str) + (count_token(str) * 2) + 1);
	token_space(str, i, k, fix_str);
	if (check_token(fix_str))
	{
		data->return_value = 2;
		free(str);
		free(fix_str);
		return (NULL);
	}
	free(str);
	return (fix_str);
}
