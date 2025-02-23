/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:51:02 by txavier           #+#    #+#             */
/*   Updated: 2025/01/23 16:08:05 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	is_valid_env(const char *key)
{
	int	i;

	i = 0;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (ft_isalnum(key[i]) && key[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void split_pipes(char *input, char ***commands)
{
    int count = 0, i = 0, inside_quotes = 0;
    char quote_char = 0, *temp = input;
    char **result;

    // Contar quantos comandos existem considerando aspas
    while (*temp)
    {
        if ((*temp == '"' || *temp == '\'') && (quote_char == 0 || quote_char == *temp))
        {
            inside_quotes = !inside_quotes;
            quote_char = inside_quotes ? *temp : 0;
        }
        else if (*temp == '|' && !inside_quotes)
            count++;
        temp++;
    }
    count++; // Número de comandos é sempre 1 a mais que o número de '|'

    result = malloc((count + 1) * sizeof(char *)); // Aloca memória para os comandos

    char *start = input;
    inside_quotes = 0;
    quote_char = 0;

    while (*input)
    {
        if ((*input == '"' || *input == '\'') && (quote_char == 0 || quote_char == *input))
        {
            inside_quotes = !inside_quotes;
            quote_char = inside_quotes ? *input : 0;
        }
        else if (*input == '|' && !inside_quotes)
        {
            *input = '\0'; // Substitui o '|' por '\0'
            result[i++] = strdup(start); // Copia o comando sem o '|'
            start = input + 1; // Atualiza o início para o próximo comando
        }
        input++;
    }
    result[i++] = strdup(start); // Último comando
    result[i] = NULL;

    *commands = result; // Retorna a matriz de comandos
}
