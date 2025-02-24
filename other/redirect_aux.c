/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:17:11 by txavier           #+#    #+#             */
/*   Updated: 2025/02/11 14:33:16 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	term_redirs(t_tokens *current, t_tokens *next, int fd)
{
	if (fd > -1)
		close(fd);
	free(current->token);
	current->token = NULL;
	free(next->token);
	next->token = NULL;
}

int	reset_heredoc_line(int pipefd[2], char **line, int len_line, char **delim)
{
	if (!line || !ft_strcmp(*line, *delim))
		return (2);
	write(pipefd[1], *line, len_line);
	write(pipefd[1], "\n", 1);
	free(*line);
	return (1);
}

void	heredoc_term(char **line, int pipefd[2], char **token1, char **token2)
{
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	if (token1 && *token1)
	{
		free(*token1);
		*token1 = NULL;
	}
	if (token2 && *token2)
	{
		free(*token2);
		*token2 = NULL;
	}
}

void	save_def_fds(int *def_read, int	*def_write)
{
	*def_read = dup(STDIN_FILENO);
	*def_write = dup(STDOUT_FILENO);
}

int	process_redirection(t_tokens *current)
{
	if (!ft_strcmp(current->token, "<<"))
		handle_heredoc(current);
	else if (!ft_strcmp(current->token, "<"))
	{
		if (handle_input_redirection(current) == -1)
			return (-1);
	}
	else if (!ft_strcmp(current->token, ">"))
		handle_simple_output_redirection(current);
	else if (!ft_strcmp(current->token, ">>"))
		handle_double_output_redirection(current);
	return (0);
}
