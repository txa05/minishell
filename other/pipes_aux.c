/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:48:47 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 23:56:58 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	update_quote_state(char *temp, int *inside_quotes, char *quote_char)
{
	if ((*temp == '"' || *temp == '\'')
		&& (*quote_char == 0 || *quote_char == *temp))
	{
		*inside_quotes = !(*inside_quotes);
		if (*inside_quotes)
			*quote_char = *temp;
		else
			*quote_char = 0;
	}
}

int	count_commands(char *input)
{
	int		count;
	int		inside_quotes;
	char	quote_char;
	char	*temp;

	count = 0;
	temp = input;
	inside_quotes = 0;
	quote_char = 0;
	while (*temp)
	{
		update_quote_state(temp, &inside_quotes, &quote_char);
		if (*temp == '|' && !inside_quotes)
			count++;
		temp++;
	}
	return (count + 1);
}

void	split_into_commands(char *input, char **result)
{
	int		i;
	int		inside_quotes;
	char	quote_char;
	char	*start;

	i = 0;
	start = input;
	inside_quotes = 0;
	quote_char = 0;
	while (*input)
	{
		handle_pipe_quotes(&input, &inside_quotes, &quote_char);
		if (*input == '|' && !inside_quotes)
		{
			*input = '\0';
			result[i++] = strdup(start);
			start = input + 1;
		}
		input++;
	}
	result[i++] = strdup(start);
	result[i] = NULL;
}

void	handle_pipe_quotes(char **input, int *inside_quotes, char *quote_char)
{
	if ((**input == '"' || **input == '\'')
		&& (*quote_char == 0 || *quote_char == **input))
	{
		*inside_quotes = !(*inside_quotes);
		if (*inside_quotes)
			*quote_char = **input;
		else
			*quote_char = 0;
	}
}
