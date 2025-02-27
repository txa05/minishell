/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxy_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:28:58 by txavier           #+#    #+#             */
/*   Updated: 2025/02/27 16:38:53 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

bool	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_redirection(char *token)
{
	return (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, "<<"));
}

bool	is_pipe(char *token)
{
	return (!ft_strcmp(token, "|") || !ft_strcmp(token, "||"));
}

void	syntax_error_things(t_shell *shell)
{
	shell->last_exit = 2;
	update_exit_var(&shell->env_list, ft_strdup("2"));
	free_tokens_list(shell->tok);
	shell->tok = NULL;
}

bool	validate_syntax(char *input)
{
	t_tokens	*list;
	t_tokens	*ll;

	list = NULL;
	tokenize(input, &list);
	if (!list)
		return (false);
	if (is_pipe(list->token))
	{
		printf("syntax error near unexpected token `%s'\n", list->token);
		free_tokens_list(list);
		return (false);
	}
	ll = list;
	while (ll)
	{
		if (is_pipe(ll->token) && !ll->next)
		{
			printf("syntax error near unexpected token `%s'\n", ll->token);
			free_tokens_list(list);
			return (false);
		}
		if (is_special_char(ll->token[0])
			&& ll->next && is_special_char(ll->next->token[0]))
		{
			printf("syntax error near unexpected token `%s'\n", ll->next->token);
			free_tokens_list(list);
			return (false);
		}
		if (is_redirection(ll->token)
			&& (!ll->next || is_special_char(ll->next->token[0])))
		{
			printf("syntax error near unexpected token `newline'\n");
			free_tokens_list(list);
			return (false);
		}
		ll = ll->next;
	}
	free_tokens_list(list);
	return (true);
}
