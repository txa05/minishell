/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxy_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:28:58 by txavier           #+#    #+#             */
/*   Updated: 2025/02/24 10:43:10 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	update_shell_exit(t_shell *shell, int exit_code, char *message)
{
	shell->last_exit = exit_code;
	update_exit_var(&shell->env_list, ft_itoa(exit_code));
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	check_pipe_errors(char *input, int i, t_shell *shell)
{
	if (input[i] == '|')
	{
		if (i == 0 || input[i + 1] == '\0')
		{
			update_shell_exit(shell, 2, "|");
			return (0);
		}
		if (input[i + 1] == '|')
		{
			update_shell_exit(shell, 2, "|");
			return (0);
		}
	}
	return (1);
}

int	check_redirection_errors(char *input, int i, char prev, t_shell *shell)
{
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i + 1] == '\0')
		{
			update_shell_exit(shell, 2, "new_line");
			return (0);
		}
		if (prev == '<' || prev == '>' || input[i + 1] == '|'
			|| input[i + 1] == '<' || input[i + 1] == '>')
		{
			update_shell_exit(shell, 2, &input[i + 1]);
			return (0);
		}
	}
	return (1);
}

int	check_pipe_redir_sequence(char *input, int i, t_shell *shell)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '<' || input[i + 1] == '>')
		{
			update_shell_exit(shell, 2, &input[i + 1]);
			return (0);
		}
	}
	return (1);
}

int	check_syntax_errors(char *input, t_shell *shell)
{
	int		i;
	char	prev;
	char	inside_quotes;

	i = 0;
	prev = 0;
	inside_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes)
		{
			if (!check_pipe_errors(input, i, shell))
				return (0);
			if (!check_redirection_errors(input, i, prev, shell))
				return (0);
			if (!check_pipe_redir_sequence(input, i, shell))
				return (0);
		}
		prev = input[i];
		i++;
	}
	return (1);
}
