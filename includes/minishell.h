/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:34:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/10/29 15:26:54 by ruidos-s         ###   ########.fr       */
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
	bool append;     // >> para saber se é append ou não
	bool heredoc;    // << para saber se é heredoc ou não
	char *delimiter; // << para saber qual a ultima palavra do heredoc
	struct s_command	*next;
}						t_command;

typedef struct s_envvar
{
	char				*name;
	char				*value;
	struct s_envvar		*next;
}						t_envvar;

typedef struct s_envvar_list
{
	t_envvar			*head;
}						t_envvar_list;

typedef struct s_data
{
	char				**env;
	int					original_stdin;
	int					original_stdout;
	t_command			*cmd;
	bool				close_shell;
	int					return_value;
	int					fd[2];
	int					exit_pipe[2];
	int					return_pipe[2];
}						t_data;

char					*readline(const char *prompt);
char					*ft_strtok(char *str, const char *delim);
void					close_fds(int *fd);
char					*find_executable(const char *command);
void					data_init(t_data *data, char **env);

// env_var
void					set_envvar(t_envvar_list *envvar_list, const char *name,
							const char *value);
char					*get_envvar(t_envvar_list *env_list, const char *name);
char					*replace_envvar(const char *input, int exit_status,
							t_envvar_list *env_list);
t_envvar_list			*init_env_list(void);
void					free_env_list(t_envvar_list *env_list);

// parsing
void					handle_input(char *input, t_data *data);
char					**parse_command(char *input);
int						check_if_token(char c);
int						count_token(const char *str);
char					*fix_token_space(char *str);
t_command				*lexer_to_command(t_lexer *lexer);

// execute
void					execute(t_command *cmd_list, t_data *data);
void					execute_command(char *command, char **args, char **env);
char					*get_command_input(void);
void					execute_command_or_path(t_command *cmd, t_data *data);
void					print_command_error(t_data *data, char *command, int error_type);

// pipes
void					execute_piped_commands(t_command *cmd, t_data *data);
bool					ft_parent(t_command *cmd, int *in_fd, t_data *data);
int						ft_child(int in_fd, t_command *cmd, t_data *data);
void					handle_fd(int in_fd, t_command *cmd, int fd[2]);

// redirections
int						handle_redirects(t_command *cmd, t_data *data);
int						handle_input_redirect(t_command *cmd,
							int *original_stdin);
int						handle_output_redirect(t_command *cmd,
							int *original_stdout);
int						execute_heredoc(t_command *cmd);
void					std_reset(int *original_stdin, int *original_stdout);

// builtins
bool					builtin_checker(t_command *cmd, t_data *data);
void					exit_command(t_data *data);
int						pwd_command(t_data *data);
int						cd_command(t_command cmd, t_data *data);

#endif