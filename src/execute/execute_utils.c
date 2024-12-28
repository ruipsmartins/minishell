/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:58:05 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/28 11:03:59 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path_value(t_data *data)
{
	t_envvar	*path_var;

	path_var = find_envvar(data->env_var_lst, "PATH");
	if (!path_var)
	{
		return (NULL);
	}
	return (ft_strdup(path_var->value));
}

// Função para obter o caminho do executável
char	*get_executable_path(const char *command, const char *dir)
{
	char	*full_path;
	size_t	dir_len;
	size_t	cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(command);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, dir_len + 1);
	ft_strlcat(full_path, "/", dir_len + 2);
	ft_strlcat(full_path, command, dir_len + cmd_len + 2);
	return (full_path);
}
