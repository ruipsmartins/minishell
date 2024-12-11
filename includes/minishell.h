/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:34:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/12/11 17:09:13 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

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
	bool				append;
	bool				heredoc;
	char				*delimiter;
	struct s_command	*next;
}						t_command;

typedef struct s_envvar
{
	char				*name;
	char				*value;
	struct s_envvar		*next;
}						t_envvar;

// typedef struct s_envvar_list
// {
// 	t_envvar			*head;
// }						t_envvar_list;

typedef struct s_data
{
	char				**env;
	int					original_stdin;
	int					original_stdout;
	t_command			*cmd;
	t_envvar			*env_var_lst;
	int					cmd_count;
	bool				close_shell;
	int					return_value;
	int					**fds;
	pid_t				*pids;
}						t_data;

char					*readline(const char *prompt);
char					*ft_strtok(char *str, const char *delim);
void					close_fds(int *fd);
char					*find_executable(const char *command, t_data *data);
void					data_init(t_data *data, char **env);

// quotes
int						check_quote(const char *input);
char					*get_word(char **input);
char 					*split_string(char **input);
char 					*quotes_trim(char *input);

const char				*handle_dollar_sign(const char *src, char *dst, t_envvar *env_list);
void handle_exit_status(char *dst);
const char *replace_variable(const char *src, char *dst, t_envvar *env_list);
const char *handle_quoted_dollar(const char *src, char *dst, t_envvar *env_list);
void replace_vars_in_string(const char *src, char *dst, t_envvar *env_list);

// env_var

int						count_valid_envvars(t_envvar *env_list);
size_t					calculate_final_len(const char *input, t_data *data);
void					ft_new_envvar(t_envvar **env_list, char *name,
							char *value);
t_envvar				*ft_create_env_list(char **env);
void					print_list(t_envvar *env_list);
t_envvar				*find_envvar(t_envvar *lst, char *name);
void					ft_envadd_back(t_envvar **lst, t_envvar *new);
char					**swap_list_to_array(t_envvar *env_list);
void					set_envvar(t_envvar *envvar_list, char *name,
							char *value);
char					*get_envvar(t_envvar *env_list, const char *name);
char					*replace_envvar(const char *input, t_data *data);
t_envvar				*init_env_list(void);
void					free_env_list(t_envvar *env_list);
void					free_data(t_data *data);
void					free_command_list(t_command *cmd_list);
void					free_lexer(t_lexer *lexer);

// parsing
void					handle_input(char *input, t_data *data);
void					handle_input(char *input, t_data *data);
char					**parse_command(char *input);
int						check_if_token(char c);
int						count_token(const char *str);
char					*fix_token_space(char *str);
t_command				*lexer_to_command(t_lexer *lexer);

// execute
void					execute(t_command *cmd_list, t_data *data);
int						execute_command(char *command, char **args,
							t_data *data);
char					*get_command_input(void);
void					execute_command_or_path(t_command *cmd, t_data *data);
void					print_command_error(t_data *data, char *command,
							int error_type);
bool					is_directory(char *path);
int						check_file_type(char *path);

// pipes
void 					execute_piped_commands(t_command *cmd, t_data *data);
void 					execute_child_process(int i, int **fds, t_command *cmd, t_data *data);
bool					ft_parent(t_command *cmd, int *in_fd, t_data *data);
//void					handle_fd(int in_fd, t_command *cmd, int fd[2]);
bool					should_execute_in_parent(t_command *cmd);
int						count_commands(t_command *cmd);
void					close_all_parent_pipes(t_data *data, int current_index);
void					close_all_pipes(int **fds, int pipe_count);
void					free_pipes(int **fds, int pipe_count);
//void					fork_error(void);


// redirections
int						handle_redirects(t_command *cmd, t_data *data);
int						handle_input_redirect(t_command *cmd,
							int *original_stdin);
int						handle_output_redirect(t_command *cmd,
							int *original_stdout);
int						execute_heredoc(t_command *cmd);
void					std_reset(int *original_stdin, int *original_stdout);

// builtins
bool					builtin_execute(t_command *cmd, t_data *data);
bool					builtin_checker(t_command *cmd);
void					exit_command(t_command *cmd, t_data *data);
int						pwd_command(t_data *data);
int						cd_command(t_command cmd, t_data *data);
void					echo_command(t_command *cmd);
void					env_command(t_data *data);
void					export_command(t_command *cmd, t_data *data);
void					unset_command(t_command *cmd, t_data *data);

// signals
void					setup_signals(void);
void					sigint_handler(int signum);
void					sigquit_handler(int signum);


#endif