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
	utils/utils.c \
	execute/execute.c \
	parsing/parsing.c parsing/fix_token_space.c parsing/lexer_to_command.c\
	redirections/redirections.c \
	pipes/pipes.c

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
	@mkdir -p $(dir $@)   #Cria a subpasta correspondente em obj
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
	valgrind --show-leak-kinds=all --leak-check=full --track-fds=yes --trace-children=yes ./minishell

# Evita que make limpe ficheiros desnecessariamente
.PHONY: all clean fclean re git valgrind
