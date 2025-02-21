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
		close(fd);
		free(current->token);
		current->token = NULL;
		free(next->token);
		next->token = NULL;
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
		close(fd);
		free(current->token);
		current->token = NULL;
		free(next->token);
		next->token = NULL;
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
			free(current->token);
			current->token = NULL;
			free(next->token);
			next->token = NULL;
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(current->token);
		current->token = NULL;
		free(next->token);
		next->token = NULL;
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
			if (!line || !ft_strcmp(line, delim))
				break ;
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		free(current->token);
		current->token = NULL;
		free(next->token);
		next->token = NULL;
		return (0);
	}
	return (0);
}

int	handle_redirections(t_shell *shell, int *def_read, int *def_write)
{
	t_tokens	*current;

	*def_read = dup(STDIN_FILENO);
	*def_write = dup(STDOUT_FILENO);
	if (!shell->tok || !shell->tok->token)
		return (0);
	current = shell->tok;
	while (current)
	{
		if (current->quote_flag == 0)
		{
			if (!ft_strcmp(current->token, ">"))
				handle_simple_output_redirection(current);
			else if (!ft_strcmp(current->token, ">>"))
				handle_double_output_redirection(current);
			else if (!ft_strcmp(current->token, "<"))
			{
				if (handle_input_redirection(current) == -1)
					return (-1);
			}
			else if (!ft_strcmp(current->token, "<<"))
				handle_heredoc(current);
		}
		current = current->next;
	}
	return (0);
}
