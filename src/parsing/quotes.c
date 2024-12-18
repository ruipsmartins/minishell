/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 18:57:27 by addicted          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:26 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote(const char *input)
{
	char c;

	c = 0;
	while(*input != '\0')
	{
		if(*input == '\'' || *input == '\"')
		{
			if(c == 0)
				c = *input;
			else if(c == *input)
				c = 0;
		}
		input++;
	}
	return((c == '\'') + (c == '\"') * 2);
}