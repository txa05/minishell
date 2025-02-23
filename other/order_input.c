/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:17:38 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 00:57:07 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	is_redirect(char token)
{
	if (token == '>')
		return (1);
	else if ((token == '<'))
		return (1);
	else
		return (0);
}
/*
int	reorder_tokens(char **tokens, int flag)
{
	int i = 0;
	int cmd_count = 0;
	int redir_count = 0;
	char **cmd;
	char **redir;

	i = 0;
	cmd_count = 0;
	redir_count = 0;
	cmd = NULL;
	redir = NULL;
	if (!tokens || !tokens[0])
		return 1;
	while (tokens[i] != NULL)
	{
		if (is_redirect(tokens[i]))
			redir_count += 2;
		else
			cmd_count++;
		i++;
	}
	cmd = malloc(sizeof(char *) * (cmd_count + 1));
	redir = malloc(sizeof(char *) * (redir_count + 1));
	if (!cmd || !redir)
	{
		free(cmd);
		free(redir);
		return 1;
	}
	i = 0;
	cmd_count = 0;
	redir_count = 0;
	while (tokens[i] != NULL)
	{
		if (is_redirect(tokens[i]))
		{
			redir[redir_count++] = tokens[i];
			redir[redir_count++] = tokens[i + 1];
			i += 2;
		}
		else
		{
			cmd[cmd_count++] = tokens[i];
			i++;
		}
	}
	cmd[cmd_count] = NULL;
	redir[redir_count] = NULL;
	i = 0;
	for (int j = 0; cmd[j] != NULL; j++)
		tokens[i++] = cmd[j];
	for (int j = 0; redir[j] != NULL; j++)
		tokens[i++] = redir[j];
	tokens[i] = NULL;
	if (check_syntax_errors(tokens, flag))
		return 1;
	free(cmd);
	free(redir);
	return 0;
}*/
