/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:34:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/06 11:33:34 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

char	*readline (const char *prompt);
char	*ft_strtok(char *str, const char *delim);
void	close_fds(int *fd);
char	*find_executable(const char *command);
char	**parse_command(char *input);
void	execute_command(char *command, char **args, char **env);
char	*get_command_input(void);
void	execute_path(char *command, char **args, char **env);

//pipes
void	execute_piped_commands(char ***commands, char **env);
char	***split_by_pipe(char *input);


#endif