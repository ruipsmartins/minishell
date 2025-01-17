/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:43 by addicted          #+#    #+#             */
/*   Updated: 2025/01/17 14:16:14 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}


int	in_quotes_check(char *str, int pos)  // apagar
{
	char c;
	char token;
	int i;
	bool quotes;
	
	//write(1, "enterd in quotes", 17);
	quotes = false;
	token = str[pos];
	i = 0;
	c = '\0';
	while(str[i] && i <= pos)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if(c == '\0')
			{
				c = str[i];
				quotes = true;
			}
			else if (c == str[i])
			{
				c = '\0';
				quotes = false;				
			}
		}
		i++;
	}
	// if(quotes)
	// 	printf("in_quotes");
	// else
	// 	printf("outside quotes");
	return(quotes);
}

int	check_token_error(char *str, char c, int i)
{
	if (c != '|')
	{
		if (check_if_token(str[i]) && !in_quotes_check(str, i))
		{

			return (ft_printf("1 Syntax error near `%c'\n", str[i]));
		}
		if (str[i + 1] == '\0')//&& in_quotes_check(str, i))
			return (ft_printf("2 Syntax error near `%c'\n", c));
	}
	if (str[i + 1] == '|' && !in_quotes_check(str, i))
		return (ft_printf("3 Syntax error near `%c'\n", str[i + 1]));
	return (0);
}

int	check_token(char *str)
{
	int		i;
	char	c;
	bool quotes;

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
	//printf("tokrn space str: %s\n", fix_str);
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
