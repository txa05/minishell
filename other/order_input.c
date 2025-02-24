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

int	read_check(char	*line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
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

int	check_redirection_errors(char *input, int i, t_shell *shell)
{
	if (input[i] == '<' || input[i] == '>')
	{
		if (input[i + 1] == input[i])
			i++;
		if (input[i + 1] == '<' || input[i + 1] == '>' || input[i + 1] == '|')
		{
			update_shell_exit(shell, 2, &input[i + 1]);
			return (0);
		}
		if (input[i + 1] == '\0')
		{
			update_shell_exit(shell, 2, "new_line");
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
