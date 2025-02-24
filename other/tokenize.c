/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:17 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 05:42:38 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	handle_quoted_filename(char *input, int i, t_tokens **head)
{
	char	quote_char;
	int		start;
	char	*token;

	quote_char = input[i++];
	start = i;
	while (input[i] && input[i] != quote_char)
		i++;
	if (input[i] == quote_char)
		i++;
	token = extract_token(&input[start], i - start - 1);
	add_token(head, token, 1);
	return (i);
}

int	handle_normal_filename(char *input, int i, t_tokens **head)
{
	int		start;
	char	*token;

	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<')
		i++;
	if (i > start)
	{
		token = extract_token(&input[start], i - start);
		add_token(head, token, 0);
	}
	return (i);
}

int	handle_redirection(char *input, int i, t_tokens **head)
{
	char	*token;
	int		redir_len;

	redir_len = 1;
	if ((input[i] == '>' && input[i + 1] == '>')
		|| (input[i] == '<' && input[i + 1] == '<'))
		redir_len = 2;
	token = extract_token(&input[i], redir_len);
	add_token(head, token, 0);
	i += redir_len;
	if (input[i] == '"' || input[i] == '\'')
	{
		i = handle_quoted_filename(input, i, head);
	}
	else
	{
		i = handle_normal_filename(input, i, head);
	}
	return (i);
}

int	handle_token(char *input, int i, t_tokens **head)
{
	int	quote_flag;

	quote_flag = 0;
	if (input[i] == '>' || input[i] == '<')
	{
		i = handle_redirection(input, i, head);
	}
	else
	{
		i = handle_word(input, i, head, &quote_flag);
	}
	return (i);
}

void	tokenize(char *input, t_tokens **head)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		i = handle_token(input, i, head);
	}
}
