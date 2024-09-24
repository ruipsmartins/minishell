/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:34:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/09/24 11:27:43 by addicted         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
#  endif

typedef struct s_lexer
{
    char *word;
    char *token;
    int i;
    struct s_lexer *next;
    struct s_lexer *prev;
} t_lexer;

char	*readline (const char *prompt);
char	*ft_strtok(char *str, const char *delim);
void	close_fds(int *fd);
char	*find_executable(const char *command);
char	**parse_command(char *input);
void	execute_command(char *command, char **args, char **env);
char	*get_command_input(void);
void	execute_path(char *command, char **args, char **env);
void	handle_input(char *input, char **env);

//pipes
void	execute_piped_commands(char ***commands, char **env);
char	***split_by_pipe(char *input);

//redirections
void	handle_redirections(char **args);



#endif