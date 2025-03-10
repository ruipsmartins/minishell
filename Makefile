# Nome do executável
NAME = minishell

# Compilador e flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS = -lreadline #-lncurses

# Diretórios
SRCS_DIR = src
OBJS_DIR = obj
INCLUDES = -I includes

# Lista de ficheiros fonte com subpastas
SRCS_FILES = \
	main.c \
	utils/utils.c utils/signals.c utils/clean_shell.c utils/input_checkers.c \
	parsing/parsing.c parsing/fix_token_space.c parsing/lexer_to_command.c \
	parsing/env_var.c parsing/envvar.c parsing/quotes.c parsing/quotes_env.c \
	parsing/free.c parsing/envvar_size.c parsing/replace_vars.c parsing/handler.c\
	parsing/devide_input.c parsing/handler_utils.c parsing/no_env.c\
	execute/execute.c execute/pipes.c  execute/pipes_utils.c execute/execute_utils.c \
	execute/redirections.c execute/heredoc.c \
	builtins/builtin_checker.c builtins/exit_command.c builtins/pwd_command.c builtins/cd_command.c \
	builtins/echo_command.c	builtins/env_command.c builtins/export_command.c builtins/unset_command.c \

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Regras
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LDFLAGS)

# Compilar os ficheiros fonte com subpastas
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)   # Cria a subpasta correspondente em obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR) && make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) && make fclean -C $(LIBFT_DIR) 

re: fclean all

git:
	git add . ..
	git commit -m "upload minishell"
	git push
	git status

valgrind:
	valgrind --suppressions=readline.supp  --track-fds=all --leak-check=full --show-leak-kinds=all ./minishell

# Evita que make limpe ficheiros desnecessariamente
.PHONY: all clean fclean re git valgrind
