/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:34:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/09 15:57:59 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64;
# endif

typedef struct s_lexer
{
	char				*word;
	char				*token;
	int					i;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				*output_file;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char				**env;
	int					original_stdin;
	int					original_stdout;
	t_command			*cmd;
}						t_data;

char					*readline(const char *prompt);
char					*ft_strtok(char *str, const char *delim);
void					close_fds(int *fd);
char					*find_executable(const char *command);
char					**parse_command(char *input);

// execute
void					execute(t_command *cmd_list, char **env);
void					execute_command(char *command, char **args, char **env);
char					*get_command_input(void);
void					std_reset(int original_stdin, int original_stdout);
void					handle_input(char *input, char **env);
void					execute_command_or_path(t_command *cmd, char **env);

// pipes
void					execute_piped_commands(t_command *cmd, t_data data);
void					ft_child(int in_fd, t_command *cmd, int fd[2],
							t_data data);
void					handle_fd(int in_fd, t_command *cmd, int fd[2]);
char					***split_by_pipe(char *input);

// redirections
int						handle_redirects(t_command *cmd, t_data data);
int						handle_input_redirect(t_command *cmd,
							int *original_stdin);
int						handle_output_redirect(t_command *cmd,
							int *original_stdout);

#endif