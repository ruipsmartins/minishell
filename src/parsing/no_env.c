/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:45:26 by duamarqu          #+#    #+#             */
/*   Updated: 2025/01/18 14:22:47 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_shlvl(t_envvar *head)
{
	t_envvar	*shlvl;
	char		*new_value;

	shlvl = find_envvar(head, "SHLVL");
	new_value = ft_itoa(ft_atoi(shlvl->value) + 1);
	if(ft_atoi(shlvl->value) < 0)
		set_envvar(head, "SHLVL", "1");
	if(ft_atoi(shlvl->value) > 100)
	{
		print_error("Warning: shell level (100) too high, resetting to 1\n", NULL, 0);
		set_envvar(head, "SHLVL", "1");
	}
	else
	set_envvar(head, "SHLVL", ft_itoa(ft_atoi(shlvl->value) + 1));
	free(new_value);
}
