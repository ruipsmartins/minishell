/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:43 by addicted          #+#    #+#             */
/*   Updated: 2024/12/18 15:59:17 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int	check_token(char *str)
{
	int		i;
	char	c;
	
	i = 0;
	while(str[i++])
	{
		if(check_if_token(str[i]))
		{
			c = str[i];
			if ((str[i] == '>' || str[i] == '<') && str[i + 1] == str[i])
				i++;
			while(str[i + 1] == ' ')
				i++;
			if (c != '|')
			{
				if (check_if_token(str[i + 1]))
					return (ft_printf("%d\n",ft_printf("minishell: syntax error near unexpected token `%c'\n", str[i + 1])));
				if(str[i + 1] == '\0')
					return (ft_printf("minishell: syntax error near unexpected token `%c'\n", c));
			}
			if (str[i + 1] == '|')
				return (ft_printf("Minishell: syntax error near unexpected token `%c'\n", str[i +1]));
		}
	}
	return (0);
}


char *fix_token_space(char *str)
{
	int i;
	int k;
	char *fix_str;
	
	i = 0;
	k = 0;
	fix_str = malloc(sizeof(char) * (ft_strlen(str) + (count_token(str) * 2) + 1));
	
	if (check_token(str))
	{
		free(str);
		return (NULL);
	}
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
			else if (str[i + 1] != str[i] && str[i + 1] )
				fix_str[++k] = ' ';
		}
		else
			fix_str[k] = str[i];
		k++;
		i++;
	}
	fix_str[k] = '\0';
	free(str);
	return (fix_str);
}
