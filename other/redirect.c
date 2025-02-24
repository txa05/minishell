/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:57:27 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 18:07:32 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	handle_simple_output_redirection(t_tokens *current)
{
	int			fd;
	t_tokens	*next;

	if (!current || !current->next)
		return (-1);
	next = current->next;
	if (current->quote_flag == 0 && !ft_strcmp(current->token, ">"))
	{
		fd = open(next->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		term_redirs(&current, &next, &fd);
		return (0);
	}
	return (0);
}

int	handle_double_output_redirection(t_tokens *current)
{
	int			fd;
	t_tokens	*next;

	if (!current || !current->next)
		return (-1);
	next = current->next;
	if (current->quote_flag == 0 && !ft_strcmp(current->token, ">>"))
	{
		fd = open(next->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		term_redirs(&current, &next, &fd);
		return (0);
	}
	return (0);
}

int	handle_input_redirection(t_tokens *current)
{
	int			fd;
	t_tokens	*next;

	if (!current || !current->next)
		return (-1);
	next = current->next;
	if (current->quote_flag == 0 && !ft_strcmp(current->token, "<"))
	{
		fd = open(next->token, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(next->token, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			term_redirs(&current, &next, &fd);
			return (-1);
		}
		term_redirs(&current, &next, &fd);
		return (0);
	}
	return (0);
}

int	handle_heredoc(t_tokens *current)
{
	int			pipefd[2];
	char		*line;
	char		*delim;
	t_tokens	*next;

	if (!current || !current->next)
		return (-1);
	next = current->next;
	if (current->quote_flag == 0 && !ft_strcmp(current->token, "<<"))
	{
		delim = next->token;
		pipe(pipefd);
		while (1)
		{
			line = readline("> ");
			if (reset_heredoc_line(pipefd,
					&line, ft_strlen(line), &delim) == 2)
				break ;
		}
		heredoc_term(&line, pipefd, &current->token, &next->token);
		return (0);
	}
	return (0);
}

int	handle_redirections(t_shell *shell, int *def_read, int *def_write)
{
	t_tokens	*current;

	save_def_fds(def_read, def_write);
	if (!shell->tok || !shell->tok->token)
		return (0);
	current = shell->tok;
	while (current)
	{
		if (current->quote_flag == 0)
		{
			if (process_redirection(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
