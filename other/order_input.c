/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:17:38 by txavier           #+#    #+#             */
/*   Updated: 2025/02/19 07:24:28 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	is_redirect(char *token)
{
    return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 ||
           ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

int	check_syntax_errors(char **tokens, int flag)
{
	int	i;

	i = 0;
	if (!tokens || !tokens[0])
		return (1);
	while (tokens[i] != NULL)
	{
		if (is_redirect(tokens[i]))
		{
			if (flag)
			{
				flag -= 1;
				i++;
			}
			else
			{
				if (tokens[i + 1] == NULL)
				{
					ft_putstr_fd("Erro de sintaxe: redirecionamento sem argumento.\n", 2);
					return 1;
				}
				if (is_redirect(tokens[i + 1]))
				{
					ft_putstr_fd("Erro de sintaxe: redirecionamento seguido de outro redirecionamento.\n", 2);
					return 1;
				}
				i += 2;
			}
		}
		else
		{
			i++;
		}
	}
	return 0;
}

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
}
