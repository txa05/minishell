/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:17 by txavier           #+#    #+#             */
/*   Updated: 2025/01/23 16:08:27 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char	*skip_delimiters(char *current, const char *delim,
			int in_quot, char *str)
{
	if (str != NULL)
		current = str;
	while (*current && ft_strchr(delim, *current) && !in_quot)
		current++;
	return (current);
}

static char	*terminate_token(char *current)
{
	if (*current)
	{
		*current = '\0';
		current++;
	}
	return (current);
}

static void	handle_quotes(char c, int *in_quot, char *quote_char)
{
	if ((c == '"' || c == '\'') && *in_quot == 0)
	{
		*in_quot = 1;
		*quote_char = c;
	}
	else if (c == *quote_char && *in_quot)
		*in_quot = 0;
}

char	*my_strtok(char *str, const char *delim)
{
	static char	*current = NULL;
	char		*start;
	int			in_quot;
	char		quote_char;

	in_quot = 0;
	quote_char = '\0';
	current = skip_delimiters(current, delim, in_quot, str);
	if (*current == '\0')
		return (NULL);
	start = current;
	while (*current)
	{
		handle_quotes(*current, &in_quot, &quote_char);
		if (ft_strchr(delim, *current) && !in_quot)
			break ;
		current++;
	}
	current = terminate_token(current);
	return (start);
}
