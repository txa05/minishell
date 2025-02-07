/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:36:33 by txavier           #+#    #+#             */
/*   Updated: 2025/01/08 17:19:55 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

void	clean_token(const char *token, char *cleaned_token)
{
	int		j;
	int		k;
	int		in_quot;
	char	quote_char;

	j = 0;
	k = 0;
	in_quot = 0;
	quote_char = '\0';
	while (token[j])
	{
		if ((token[j] == '"' || token[j] == '\'') && in_quot == 0)
		{
			in_quot = 1;
			quote_char = token[j];
		}
		else if (token[j] == quote_char && in_quot)
			in_quot = 0;
		else
			cleaned_token[k++] = token[j];
		j++;
	}
	cleaned_token[k] = '\0';
}

int	process_token(const char *token, char **args, int i)
{
	int		len;
	char	*cleaned_token;

	len = 0;
	if (!token)
		return (0);
	len = ft_strlen(token);
	cleaned_token = (char *)malloc(len + 1);
	if (!cleaned_token)
		return (0);
	clean_token(token, cleaned_token);
	args[i] = cleaned_token;
	if (!args[i])
	{
		free(cleaned_token);
		return (i);
	}
	return (i + 1);
}

void	tokenize_inputs(char *input, char **args)
{
	int		i;
	int		prev_i;
	char	*token;

	i = 0;
	prev_i = 0;
	if (!input)
		return ;
	input[ft_strcspn(input, "\n")] = '\0';
	token = my_strtok(input, " ");
	while (token != NULL)
	{
		prev_i = i;
		i = process_token(token, args, i);
		if (i == -1 || i == prev_i)
		{
			free_tokens(args);
			return ;
		}
		token = my_strtok(NULL, " ");
	}
	args[i] = NULL;
}
