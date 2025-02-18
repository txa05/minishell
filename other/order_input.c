/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:17:38 by txavier           #+#    #+#             */
/*   Updated: 2025/02/13 18:12:35 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
char	*reorder_input(const char *input)
{
    char	**commands = NULL;   // Para armazenar os comandos e argumentos
    char	**redirects = NULL;  // Para armazenar os redirecionamentos
    char	*result;
    char	*temp = strdup(input);
    char	*token;
    int cmd_count = 0, redir_count = 0, len = 0;

    if (!temp)
        return NULL;

    // Contar o número de tokens
    int	total_tokens = 0;
    char	*temp_count = strdup(input);
    token = strtok(temp_count, " ");
    while (token)
    {
        total_tokens++;
        token = strtok(NULL, " ");
    }
    free(temp_count);

    // Alocar espaço para os tokens dinamicamente
    commands = malloc(sizeof(char *) * total_tokens);
    redirects = malloc(sizeof(char *) * total_tokens);
    if (!commands || !redirects)
    {
        free(temp);
        free(commands);
        free(redirects);
        return NULL;
    }

    // Separar tokens em comandos e redirecionamentos
    token = strtok(temp, " ");
    while (token)
    {
        if (strcmp(token, ">") == 0 || strcmp(token, "<") == 0 || 
            strcmp(token, ">>") == 0 || strcmp(token, "<<") == 0)
        {
            // Adiciona o redirecionamento na lista
            redirects[redir_count++] = strdup(token);
            // O próximo token deve ser o nome do arquivo
            token = strtok(NULL, " ");
            if (token)
                redirects[redir_count++] = strdup(token);
        }
        else
        {
            // Adiciona argumentos normais na lista de comandos
            commands[cmd_count++] = strdup(token);
        }
        token = strtok(NULL, " ");
    }

    // Calcular tamanho do resultado final
    for (int i = 0; i < cmd_count; i++)
        len += strlen(commands[i]) + 1;
    for (int i = 0; i < redir_count; i++)
        len += strlen(redirects[i]) + 1;

    result = malloc(len + 1); // +1 para o '\0'
    if (!result)
    {
        free(temp);
        for (int i = 0; i < cmd_count; i++) free(commands[i]);
        for (int i = 0; i < redir_count; i++) free(redirects[i]);
        free(commands);
        free(redirects);
        return NULL;
    }

    result[0] = '\0';

    // Adiciona os comandos primeiro
    for (int i = 0; i < cmd_count; i++)
    {
        strcat(result, commands[i]);
        if (i < cmd_count - 1)
            strcat(result, " ");
    }

    // Adiciona os redirecionamentos no final
    for (int i = 0; i < redir_count; i++)
    {
        strcat(result, " ");
        strcat(result, redirects[i]);
    }

    // Liberar memória alocada
    free(temp);
    for (int i = 0; i < cmd_count; i++) free(commands[i]);
    for (int i = 0; i < redir_count; i++) free(redirects[i]);
    free(commands);
    free(redirects);

    return result;
}
