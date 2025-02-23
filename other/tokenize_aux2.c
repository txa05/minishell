/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_aux2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 08:25:17 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 09:25:37 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*extract_token(char *start, int length)
{
	char	*token;

	token = malloc(length + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, start, length);
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
		return (NULL);
	ft_strcpy(new_token, token1);
	ft_strcat(new_token, token2);
	free(token1);
	free(token2);
	return (new_token);
}

int	skip_spaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

int	handle_normal_part(char *input, int i, char **token)
{
	int		start;
	char	*normal_part;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<'
		&& input[i] != '"' && input[i] != '\'')
		i++;
	normal_part = extract_token(&input[start], i - start);
	if (*token)
		*token = concat_tokens(*token, normal_part);
	else
		*token = normal_part;
	return (i);
}

int	handle_quoted_part(char *input, int i, char **token, int *quote_flag)
{
	char	quote;
	int		start;
	char	*quoted_part;

	quote = input[i++];
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	quoted_part = extract_token(&input[start], i - start - 1);
	if (*token)
		*token = concat_tokens(*token, quoted_part);
	else
		*token = quoted_part;
	*quote_flag = 1;
	return (i);
}
