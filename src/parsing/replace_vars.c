/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:16:33 by duamarqu          #+#    #+#             */
/*   Updated: 2024/12/30 13:25:26 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_quotes(const char **src, char **dst, int *quote_flag)
{
	*quote_flag = !(*quote_flag);
	*(*dst)++ = *(*src)++;
}

void	handle_single_quotes(const char **src, char **dst,
int in_double_quotes, int *in_single_quotes)
{
	if (!in_double_quotes)
		toggle_quotes(src, dst, in_single_quotes);
	else
		*(*dst)++ = *(*src)++;
}

void	replace_vars(const char *input, char *result, t_data *data)
{
	const char	*src;
	char		*dst;
	int			in_double_quotes;
	int			in_single_quotes;

	dst = result;
	src = input;
	in_double_quotes = 0;
	in_single_quotes = 0;
	while (*src)
	{
		if (*src == '\"')
			toggle_quotes(&src, &dst, &in_double_quotes);
		else if (*src == '\'')
			handle_single_quotes(&src, &dst, in_double_quotes,
				&in_single_quotes);
		else if (*src == '$' && (!in_single_quotes || in_double_quotes))
			process_envvar(&src, &dst, data);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}
