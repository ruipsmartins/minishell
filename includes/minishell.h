/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: duamarqu <duamarqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:34:50 by ruidos-s          #+#    #+#             */
/*   Updated: 2025/01/17 18:15:23 by duamarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>

extern int				g_var;

typedef struct s_lexer
{
	char				*word;
	char				*token;
	int					i;
	struct s_lexer		*next;
	struct s_lexer		*prev;
}						t_lexer;

typedef struct s_redirect
{
	char				*out_file;
	bool				append;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_heredoc
{
	char				*delimiter;
	bool				heredoc;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_input
{
	char				*file_name;
	struct s_input		*next;
}						t_input;

typedef struct s_quotes
{
	char	*token;
	int		quotes;
	int		in_single;
	int		in_double;
}						t_quotes;

typedef struct s_command
{
	char				**args;
	// char			*input_file;//para apagar
	t_input				*input;
	t_redirect			*redirect;
	//	char			*out_file;
	// bool				heredoc;
	t_heredoc			*heredoc;
	struct s_command	*next;
	int					i;
}						t_command;

typedef struct s_envvar
{
	char				*name;
	char				*value;
	struct s_envvar		*next;
}						t_envvar;

typedef struct s_data
{
	char				**env;
	char				*executable;
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

// input
int						only_spaces(char *input);
int						check_4_pipe(char *input, t_data *data);
int						check_here_doc(char *input, t_data *data);
char					*ft_strtok(char *str, const char *delim);
void					data_init(t_data *data, char **env);
void					handle_pipe_token(t_command **current_cmd,
							int *arg_count);
t_lexer					*handle_append(t_lexer *current,
							t_command **current_cmd, t_command **cmd_list);
t_lexer					*handle_heredoc(t_lexer *current,
							t_command **current_cmd, t_command **cmd_list);
t_lexer					*handle_output(t_lexer *current,
							t_command **current_cmd, t_command **cmd_list,
							bool append);
t_lexer					*handle_input_redirection(t_lexer *current,
							t_command **current_cmd, t_command **cmd_list);
t_lexer					*handle_token(t_lexer *current, t_command **current_cmd,
							t_command **cmd_list, int *arg_count);
t_lexer					*devide_input(char *input);
int						is_token(const char *str);
int						only_spaces(char *input);

// quotes
int						check_quote(const char *input);
char					*split_string(char **input, t_quotes *quotes);

// env_var
void					set_envvar(t_envvar *envvar_list, char *name,
							char *value);
char					*find_envvar_value(t_envvar *env_var_lst,
							char *var_name);
char					*extract_var_name(const char **src);
size_t					handle_variable(const char **src, t_data *data);
void					replace_vars(const char *input, char *result,
							t_data *data);
void					process_envvar(const char **src, char **dst,
							t_data *data);
const char				*get_envvar_value(const char *start, const char *end,
							t_envvar *env_list);
char					*skip_spaces(char *input);
int						check_if_token(char c);
int						count_token(const char *str);
t_command				*lexer_to_command(t_lexer *lexer);
int						size_return(int return_value);
size_t					calculate_final_len(const char *input, t_data *data);
int						count_valid_envvars(t_envvar *env_list);
size_t					calculate_final_len(const char *input, t_data *data);
void					ft_new_envvar(t_envvar **env_list, char *name,
							char *value);
t_envvar				*ft_create_env_list(char **env);
t_envvar				*find_envvar(t_envvar *lst, char *name);
void					ft_envadd_back(t_envvar **lst, t_envvar *new);
char					**swap_list_to_array(t_envvar *env_list);
void					set_envvar(t_envvar *envvar_list, char *name,
							char *value);
char					*get_envvar(t_envvar *env_list, const char *name);
char					*get_env_value(char *input);
char					*get_env_name(char *input);
t_envvar				*ft_last_env(t_envvar *lst);
char					*replace_envvar(const char *input, t_data *data);
void					cleanup_data(t_data *data);
void					free_command_list(t_command *cmd_list);
void					free_lexer(t_lexer *lexer);
void					free_env_list(t_envvar *env_list);
t_envvar				*no_env(t_envvar *head);
void					free_heredoc(t_command *current);
void					free_input(t_command *current);

// parsing
void					handle_input(char *input, t_data *data);
void					handle_input(char *input, t_data *data);
int						check_if_token(char c);
int						count_token(const char *str);
char					*fix_token_space(char *str, t_data *data);
t_command				*lexer_to_command(t_lexer *lexer);
int						in_quotes_check(char *str, int pos);

void					helper_output(t_command **current_cmd,
							t_redirect *new_redirect, t_lexer *current,
							bool append);
void					helper_heredoc(t_command **current_cmd,
							t_heredoc *new_heredoc, t_lexer *current);
void					helper_input(t_command **curent_cmd, t_input *new_input,
							t_lexer *current);
int						start_pipe(char *input, t_data *data);
// execute
void					execute(t_command *cmd_list, t_data *data);
int						execute_command(char *command, char **args,
							t_data *data);
char					*get_command_input(t_data *data);
char					*get_executable_path(const char *command,
							const char *dir);
char					*get_path_value(t_data *data);
char					*find_executable(const char *command, t_data *data);
void					execute_command_or_path(t_command *cmd, t_data *data);
void					print_command_error(t_data *data, char *command,
							int error_type);
int						check_file_type(char *path);

// pipes
void					execute_piped_commands(t_command *cmd, t_data *data);
void					execute_child_process(int i, int **fds, t_command *cmd,
							t_data *data);
bool					should_execute_in_parent(t_command *cmd);
int						count_commands(t_command *cmd);
void					close_all_parent_pipes(t_data *data, int current_index);
void					close_all_pipes(int **fds, int pipe_count);
void					free_pipes(int **fds, int pipe_count);

// redirections
int						handle_redirects(t_command *cmd, t_data *data);
int						handle_input_redirect(t_command *cmd,
							int *original_stdin);
int						handle_output_redirect(t_command *cmd,
							int *original_stdout);
int						execute_heredoc(t_command *cmd);

// builtins
bool					builtin_execute(t_command *cmd, t_data *data);
// bool					builtin_checker(t_command *cmd);
void					exit_command(t_command *cmd, t_data *data);
int						pwd_command(t_data *data);
int						cd_command(t_command cmd, t_data *data);
void					echo_command(t_command *cmd, t_data *data);
void					env_command(t_data *data);
void					export_command(t_command *cmd, t_data *data);
void					unset_command(t_command *cmd, t_data *data);

// signals.c
void					handle_here_doc_exit(int signal);
void					ctrl_c_child(int signal);
void					ctrl_c_parent(int signal);

// utils
void					cleanup_child_data(t_data *data);
void					cleanup_data(t_data *data);

#endif