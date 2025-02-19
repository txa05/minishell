/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:14:47 by txavier           #+#    #+#             */
/*   Updated: 2025/02/19 16:33:24 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_tokens
{
    char            *token;
    int             quote_flag;
    struct s_tokens *next;
}   t_tokens;

/* Cria um novo nó da lista encadeada */
t_tokens *new_token(char *token, int quote_flag)
{
    t_tokens *new = malloc(sizeof(t_tokens));
    if (!new)
        return NULL;
    new->token = strdup(token);
    new->quote_flag = quote_flag;
    new->next = NULL;
    return new;
}

/* Adiciona um novo nó ao final da lista */
void add_token(t_tokens **head, char *token, int quote_flag)
{
    t_tokens *new = new_token(token, quote_flag);
    if (!new)
        return;
    if (!(*head))
    {
        *head = new;
        return;
    }
    t_tokens *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

/* Copia um trecho da string para um novo buffer */
char *extract_token(char *start, int length)
{
    char *token = malloc(length + 1);
    if (!token)
        return NULL;
    strncpy(token, start, length);
    token[length] = '\0';
    return token;
}

/* Função para dividir a string em tokens e identificar aspas */
void tokenize(char *input, t_tokens **head)
{
    int i = 0, start, quote_flag;
    while (input[i])
    {
        while (input[i] == ' ') // Ignora espaços
            i++;
        if (!input[i]) // Se chegar ao final da string
            break;
        
        start = i;
        quote_flag = 0;
        
        // Se encontrar aspas, define quote_flag e encontra o fechamento
        if (input[i] == '"' || input[i] == '\'')
        {
            char quote = input[i++];
            start = i;
            while (input[i] && input[i] != quote)
                i++;
            quote_flag = 1;
            if (input[i] == quote) // Se encontrar o fechamento da aspa
            {
                add_token(head, extract_token(&input[start], i - start), quote_flag);
                i++; // Pula o caractere da aspa de fechamento
            }
        }
        else // Caso contrário, separa por espaços
        {
            while (input[i] && input[i] != ' ')
                i++;
            add_token(head, extract_token(&input[start], i - start), quote_flag);
        }
    }
}

/* Função para imprimir a lista de tokens */
void print_tokens(t_tokens *head)
{
    while (head)
    {
        printf("Token: %s | Quote_flag: %d\n", head->token, head->quote_flag);
        head = head->next;
    }
}

/* Função para liberar a lista */
void free_tokens(t_tokens *head)
{
    t_tokens *temp;
    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->token);
        free(temp);
    }
}

/* Exemplo de uso */
int main()
{
    char input[] = "hello \"    world test            \" '42 is great' example";
    t_tokens *token_list = NULL;

    tokenize(input, &token_list);
    print_tokens(token_list);
    free_tokens(token_list);

    return 0;
}

