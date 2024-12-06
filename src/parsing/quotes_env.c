/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addicted <addicted@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:47:59 by addicted          #+#    #+#             */
/*   Updated: 2024/12/06 12:21:13 by addicted         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handle_exit_status(char *dst)
// {
//     // Implemente a lógica para substituir `$?` pelo código de saída apropriado
//     const char *exit_status = "0"; // Exemplo fixo
//     strcpy(dst, exit_status);      // Use `ft_strcpy` no lugar de `strcpy`
// }

// const char *replace_variable(const char *src, char *dst, t_envvar *env_list)
// {
//     const char *start = src;
//     char *var_name;
//     const char *value;

//     while (*src && (isalnum(*src) || *src == '_')) // Use `ft_isalnum` no lugar de `isalnum`
//         src++;

//     var_name = strndup(start, src - start); // Use `ft_strndup` no lugar de `strndup`
//     value = find_envvar(env_list, var_name)->value;

//     if (value != NULL)
//     {
//         strcpy(dst, value); // Use `ft_strcpy` no lugar de `strcpy`
//     }
//     else
//     {
//         fprintf(stderr, "%s not found\n", var_name);
//     }

//     free(var_name);
//     return src;
// }

// const char *handle_quoted_dollar(const char *src, char *dst, t_envvar *env_list)
// {
//     char quote = *src++;
//     while (*src && *src != quote)
//     {
//         if (*src == '$' && quote == '\"')
//         {
//             src = handle_dollar_sign(src, dst, env_list);
//             dst += strlen(dst);
//         }
//         else
//         {
//             *dst++ = *src++;
//         }
//     }
//     return (*src == quote) ? src + 1 : src; // Pula a aspas final se existir
// }
// const char *handle_dollar_sign(const char *src, char *dst, t_envvar *env_list)
// {
//     src++; // Avança para o próximo caractere após `$`

//     if (*src == '?')
//     {
//         handle_exit_status(dst); // Função para tratar `$?` (se necessário)
//         return src + 1;          // Avança após `$?`
//     }
//     else if (*src == '\'' || *src == '\"')
//     {
//         src = handle_quoted_dollar(src, dst, env_list);
//     }
//     else
//     {
//         src = replace_variable(src, dst, env_list);
//     }
//     return src;
// }
// void replace_vars_in_string(const char *src, char *dst, t_envvar *env_list)
// {
//     while (*src)
//     {
//         if (*src == '$')
//         {
//             src = handle_dollar_sign(src, dst, env_list);
//             dst += strlen(dst); // Move o ponteiro `dst` para o final da string copiada
//         }
//         else
//         {
//             *dst++ = *src++;
//         }
//     }
//     *dst = '\0';
// }


// char *replace_envvar(const char *input, t_envvar *env_list)
// {
//     char *result;
//     size_t len;

//     len = calculate_final_len(input, env_list);
//     if (len == 0)
//     {
//         fprintf(stderr, "Error calculating final length\n");
//         return NULL;
//     }

//     result = (char *)calloc(len + 2, sizeof(char)); // calloc deve ser substituído por ft_calloc
//     if (result == NULL)
//     {
//         perror("calloc");
//         exit(EXIT_FAILURE);
//     }

//     replace_vars_in_string(input, result, env_list);
//     return result;
// }

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Função auxiliar para alocar memória para a string resultante
static char *allocate_result(size_t len)
{
    char *result = (char *)calloc(len + 2, sizeof(char)); // Trocar para ft_calloc, se necessário
    if (result == NULL)
    {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return result;
}

// // Função para calcular o comprimento final da string resultante
// static size_t TTcalculate_final_len(const char *input, t_envvar *env_list)
// {
//     // Lógica para calcular o comprimento final aqui
//     return strlen(input); // Exemplo simplificado, ajuste com lógica real
// }

// Função para obter o valor da variável de ambiente
static const char *get_envvar_value(const char *start, const char *end, t_envvar *env_list)
{
    char *var_name;
    const char *value;
    
    var_name = strndup(start, end - start); // Trocar para ft_strndup, se necessário
    if(find_envvar(env_list, var_name))
        value = find_envvar(env_list, var_name)->value;
    else
        value = "";
    free(var_name);
    return value;
}

// Função para processar variáveis de ambiente
static void process_envvar(const char **src, char **dst, t_envvar *env_list)
{
    const char *start = ++(*src);
    while (**src && (isalnum(**src) || **src == '_')) // Trocar para ft_isalnum, se necessário
        (*src)++;
    const char *value = get_envvar_value(start, *src, env_list);
    if (value == NULL)
    {
        printf("Variable not found\n");
        exit(EXIT_FAILURE);
    }
    strcpy(*dst, value);   // Trocar para ft_strcpy, se necessário
    *dst += strlen(value); // Trocar para ft_strlen, se necessário
}

// Função principal para substituir variáveis
// static void replace_vars(const char *input, char *result, t_envvar *env_list)
// {
//     const char *src = input;
//     char *dst = result;
//     int in_double_quotes = 0;

//     while (*src)
//     {
//         if (*src == '\"') // Alternar o estado de aspas duplas
//         {
//             in_double_quotes = !in_double_quotes;
//             *dst++ = *src++;
//         }
//         else if (*src == '\'' && !in_double_quotes) // Ignorar aspas simples fora de aspas duplas
//         {
//             *dst++ = *src++;
//             while (*src && *src != '\'')
//                 *dst++ = *src++;
//         }
            
//         else if (*src == '$' && (in_double_quotes || !strchr("\'\"", *(src + 1))))
//             process_envvar(&src, &dst, env_list);
//         else
//             *dst++ = *src++;
//     }
//     *dst = '\0';
// }

static void replace_vars(const char *input, char *result, t_envvar *env_list)
{
    const char *src = input;  // Ponteiro para ler a entrada
    char *dst = result;       // Ponteiro para escrever no resultado
    int in_double_quotes = 0; // Flag para indicar se estamos dentro de aspas duplas
    int in_single_quotes = 0; // Flag para indicar se estamos dentro de aspas simples

    while (*src)
    {
        if (*src == '\"') // Alternar estado de aspas duplas
        {
            in_double_quotes = !in_double_quotes;
            *dst++ = *src++; // Copiar aspas duplas para a saída
        }
        else if (*src == '\'' && !in_double_quotes) // Aspas simples fora de aspas duplas
        {
            in_single_quotes = !in_single_quotes;
            *dst++ = *src++; // Copiar aspas simples para a saída
        }
        else if (*src == '\'' && in_double_quotes) // Aspas simples dentro de aspas duplas
        {
            *dst++ = *src++; // Copiar aspas simples para a saída sem alternar o estado
        }
        else if (*src == '$' && (!in_single_quotes || in_double_quotes)) // Substituir variáveis
        {
            process_envvar(&src, &dst, env_list);
        }
        else
        {
            *dst++ = *src++; // Copiar outros caracteres
        }
    }
    *dst = '\0'; // Finalizar a string
}

// Função principal
char *replace_envvar(const char *input, t_envvar *env_list)
{
    size_t len = calculate_final_len(input, env_list);
    if (len == 0)
    {
        ft_printf("Error calculating final length\n");
        return NULL;
    }
    char *result = allocate_result(len);
    replace_vars(input, result, env_list);
    return result;
}
