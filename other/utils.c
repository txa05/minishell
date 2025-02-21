/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:36:33 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 20:16:49 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_tokens_list(t_tokens *list)
{
	t_tokens	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->token)
			free(temp->token);
		temp->token = NULL;
		if (temp)
			free(temp);
		temp = NULL;
	}
	list = NULL;
}

/* Cria um novo nó da lista encadeada */
t_tokens	*new_token(char *token, int quote_flag)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return NULL;
	new->token = token;
	new->quote_flag = quote_flag;
	new->next = NULL;
	return (new);
}

void	print_tokens(t_tokens *head)
{
	t_tokens *current;
	
	current = head;
    while (current)
    {
        printf("Token: \"%s\" | Quote_flag: %d\n", current->token, current->quote_flag);
        current = current->next;
    }
}

void	add_token(t_tokens **list, char *token, int quote_flag)
{
	t_tokens	*new;
	t_tokens	*temp;

	temp = NULL;
	new = new_token(token, quote_flag);
	if (!new)
		return;
	if (!(*list))
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_strncpy(char *dest, char *src, int i)
{
	int	j;

	j = 0;
	if (!src)
		return ;
	while (i > 0 && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
		i--;
	}
}

char	*extract_token(char *start, int length)
{
	char	*token;

	token = malloc(length + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, start, length);
	token[length] = '\0';
	return (token);
}

char	*concat_tokens(char *token1, char *token2)
{
	int		len1;
	int		len2;
	char	*new_token;

	len1 = strlen(token1);
	len2 = strlen(token2);
	new_token = malloc(len1 + len2 + 1);
	if (!new_token)
		return NULL;
	strcpy(new_token, token1);
	strcat(new_token, token2);
	free(token1);
	free(token2);
	return (new_token);
}

/* Função para dividir a string em tokens e identificar aspas */
void tokenize(char *input, t_tokens **head)
{
    int i = 0, start;
    int quote_flag = 0;

    while (input[i])
    {
        while (input[i] == ' ') // Ignora espaços
            i++;
        if (!input[i]) // Se chegar ao final da string
            break;

        start = i;
        quote_flag = 0;
        char *token = NULL;

        // Se encontrar aspas, captura o conteúdo dentro e após elas
        if (input[i] == '"' || input[i] == '\'')
        {
            char quote = input[i++];
            start = i;

            while (input[i] && input[i] != quote)
                i++;

            if (input[i] == quote) // Fecha aspas corretamente
                i++;

            token = extract_token(&input[start], i - start - 1);
            quote_flag = 1;

            // Captura caracteres após as aspas que pertencem ao mesmo token
            start = i;
            while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<' &&
                   input[i] != '"' && input[i] != '\'')
                i++;

            if (i > start)
            {
                char *extra_part = extract_token(&input[start], i - start);
                token = concat_tokens(token, extra_part);
            }
        }
        else if (input[i] == '>' || input[i] == '<') // Redirecionadores
        {
            token = extract_token(&input[i], 1);
            add_token(head, token, quote_flag);
            i++;

            // Se houver um caractere após o '>', trata separadamente
            if (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<')
            {
                start = i;
                while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<')
                    i++;

                token = extract_token(&input[start], i - start);
                add_token(head, token, quote_flag);
            }
            continue;
        }
        else // Tokens normais
        {
            while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<' &&
                   input[i] != '"' && input[i] != '\'')
                i++;
            token = extract_token(&input[start], i - start);
        }

        add_token(head, token, quote_flag);
    }
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		if (tokens)
		{
			free(tokens[i]);
			i++;
		}
	}
	free(tokens);
	tokens = NULL;
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	quoted_redir(int *flag, char *token)
{
	if (!ft_strcmp("\">\"", token) || !ft_strcmp("\">>\"", token) 
		|| !ft_strcmp("\"<\"", token)
		|| !ft_strcmp("\"<<\"", token))
		*flag += 1;
}

