/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:57:27 by txavier           #+#    #+#             */
/*   Updated: 2025/01/31 18:56:55 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	handle_simple_output_redirection(char **tokens, int i)
{
	int	fd;
	int	last_index;
	int	temp_fd;

	last_index = i;
	while (tokens[last_index] && !ft_strcmp(tokens[last_index], ">"))
	{
		temp_fd = open(tokens[last_index + 1],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (temp_fd == -1)
		{
			perror("open");
			return (-1);
		}
		close(temp_fd);
		last_index += 2;
	}
	fd = open(tokens[last_index - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	while (i < last_index)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		free(tokens[i + 1]);
		tokens[i + 1] = NULL;
		i += 2;
	}
	return (0);
}

int	handle_double_output_redirection(char **tokens, int i)
{
	int	fd;
	int	last_index;
	int	temp_fd;

	last_index = i;
	while (tokens[last_index] && !ft_strcmp(tokens[last_index], ">>"))
	{
		temp_fd = open(tokens[last_index + 1],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (temp_fd == -1)
		{
			perror("open");
			return (-1);
		}
		close(temp_fd);
		last_index += 2;
	}
	fd = open(tokens[last_index - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open4");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	while (i < last_index)
	{
		free(tokens[i]);
		tokens[i] = NULL;
		free(tokens[i + 1]);
		tokens[i + 1] = NULL;
		i += 2;
	}
	return (0);
}

int	handle_input_redirection(char **tokens, int i)
{
	int	fd;

	if (!ft_strcmp(tokens[i], "<"))
	{
		fd = open(tokens[i + 1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tokens[i + 1], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		free(tokens[i]);
		tokens[i] = NULL;
		free(tokens[i + 1]);
		tokens[i + 1] = NULL;
	}
	return (0);
}

int	handle_heredoc(char **tokens, int i)
{
	int		pipefd[2];
	char	*line;
	char	*delim;

	if (!ft_strcmp(tokens[i], "<<"))
	{
		delim = tokens[i + 1];
		pipe(pipefd);
		while (19)
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
		heredoc_term(tokens, i);
	}
	return (0);
}

int	handle_redirections(char **tokens, int *def_read, int *def_write, int *flag)
{
	*def_read = dup(STDIN_FILENO);
	*def_write = dup(STDOUT_FILENO);
	if (*flag == 1)
		return (0);
	execute_redirect(tokens);
	return (0);
}
