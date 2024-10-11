/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_token_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:11:43 by addicted          #+#    #+#             */
/*   Updated: 2024/10/11 18:34:42 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_if_token(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

char *fix_token_space(char *str)
{
	int i;
	int k;
	char *fix_str;
	
	i = 0;
	k = 0;
	fix_str = malloc(sizeof(char) * (strlen(str) + (count_token(str) * 2) + 1));
	while (str[i])
	{
		if (check_if_token(str[i]))
		{
			fix_str[k++] = ' ';
			fix_str[k] = str[i];
			if (str[i + 1] == str[i])
				fix_str[++k] = str[++i];
			else if (str[i + 1] != str[i] && str[i + 1])
				fix_str[++k] = ' ';
		}
		else
			fix_str[k] = str[i];
		k++;
		i++;
	}
	fix_str[k] = '\0';
	return (fix_str);
}
// int main(void)
// {
// 	// char *input = "test";
// 	char *input = "<ls -la|grep worln<d  0123|45 ii9|i|iiiii";
// 	char *env[] = {NULL}; // Dummy environment

// 	printf("strlen: %d\n", (int)strlen(input));
// 	printf("input:\n%s\n", input);
// 	input = fix_token_space(input);
// 	printf("input:\n%s\n", input);
// 	return (0);
// }