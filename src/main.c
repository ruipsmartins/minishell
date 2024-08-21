/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruidos-s <ruidos-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:28:57 by ruidos-s          #+#    #+#             */
/*   Updated: 2024/08/01 10:42:59 by ruidos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Função para dividir strings (substitui strtok)
char *ft_strtok(char *str, const char *delim) {
    static char *last;
    if (str) last = str;
    if (!last) return NULL;

    char *start = last;
    while (*last && !ft_strchr(delim, *last)) {
        last++;
    }
    if (*last) {
        *last = '\0';
        last++;
    } else {
        last = NULL;
    }
    return start;
}

char *find_executable(const char *command) {
    char *path = getenv("PATH");
    char *dir;
    char full_path[1024];

    if (!path) return NULL;

    char *path_copy = ft_strdup(path);
    if (!path_copy) return NULL;

    dir = ft_strtok(path_copy, ":");
    while (dir) {
        ft_strlcpy(full_path, dir, 1024);
        ft_strlcat(full_path, "/", 1024);
        ft_strlcat(full_path, command, 1024);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return ft_strdup(full_path);
        }
        dir = ft_strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

// Função para dividir a linha de comando em comando e argumentos
char **parse_command(char *input) {
    char **args = (char **)malloc(64 * sizeof(char *));
    if (!args) return NULL;

    char *arg;
    int i = 0;

    arg = ft_strtok(input, " ");
    while (arg) {
        args[i++] = arg;
        arg = ft_strtok(NULL, " ");
    }
    args[i] = NULL;

    return args;
}

// Função para executar o comando
void execute_command(char *command, char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Processo filho
        if (execve(command, args, NULL) == -1) {
            write(STDERR_FILENO, "execve error\n", 13);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        write(STDERR_FILENO, "fork error\n", 11);
    } else {
        // Processo pai
        waitpid(pid, &status, 0);
    }
}

int main() {
    char *input, *command;
    char **args;

    while ((input = readline("MinisHell> ")) != NULL) {
        if (*input) {
            add_history(input);

            args = parse_command(input);
            if (!args) {
                free(input);
                continue;
            }
            command = args[0];

            // Verificar se é um caminho absoluto, relativo ou só o nome do executável
            if (command[0] == '/' || command[0] == '.') {
                // Caminho absoluto ou relativo
                if (access(command, X_OK) == 0) {
                    execute_command(command, args);
                } else {
                    write(STDERR_FILENO, "Command not found\n", 18);
                }
            } else {
                // Procurar no PATH
                char *executable = find_executable(command);
                if (executable) {
                    execute_command(executable, args);
                    free(executable);
                } else {
                    write(STDERR_FILENO, "Command not found in PATH\n", 26);
                }
            }

            free(args);
        }
        free(input);
    }

    rl_clear_history();
    return 0;
}