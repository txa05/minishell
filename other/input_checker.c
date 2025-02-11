/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:12:53 by txavier           #+#    #+#             */
/*   Updated: 2025/02/11 15:17:11 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**create_matrix(char *input, int len)
{
	int		i;
	int		j;
	char	**matrix;

	i = 0;
	j = 0;
	matrix = malloc(sizeof(char *) * (len + 1));
	if (!matrix)
		return (NULL);
	while (input[i])
	{
		if (input[i] != ' ')
		{
			matrix[j] = malloc(sizeof(char) * 2);
			matrix[j][0] = input[i];
			matrix[j][1] = '\0';
			j++;
		}
		i++;
	}
	matrix[j] = NULL;
	return (matrix);
}

void	print_error(char c, int n_l)
{
	ft_putstr_fd("minishell: syntax error ", 2);
	if (n_l)
		ft_putstr_fd("near unexpected token `new_line'\n", 2);
	else
	{
		ft_putstr_fd("near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
}

int	check_redirection_errors(char **matrix, int i)
{
	if (!ft_strcmp(matrix[i], ">") && (!matrix[i + 1]
			|| !ft_strcmp(matrix[i + 1], "|")))
		return (print_error('|', 0), 0);
	if (matrix[i][0] == '>' && matrix[i + 1][0] == '>'
			&& matrix[i + 2][0] == '>')
		return (print_error('>', 0), 0);
	if (matrix[i][0] == '>' && matrix[i + 1][0] == '>'
			&& matrix[i + 2][0] == '<')
		return (print_error('<', 0), 0);
	if (matrix[i][0] == '>' && matrix[i + 1][0] == '<')
		return (print_error('<', 0), 0);
	return (1);
}

int	check_pipe_errors(char **matrix, int i)
{
	if (!ft_strcmp(matrix[i], "|") && !ft_strcmp(matrix[i + 1], "|"))
		return (print_error('|', 0), 0);
	if (matrix[0][0] == '|')
		return (print_error('|', 0), 0);
	if (matrix[i][0] == '|' && !matrix[i + 1])
		return (ft_putstr_fd("minishell: unexpected pipe\n", 2), 0);
	return (1);
}

int	validate_operators(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && matrix[i + 1])
	{
		if (!check_redirection_errors(matrix, i)
			|| !check_pipe_errors(matrix, i))
			return (0);
		i++;
	}
	return (1);
}

int	check_invalid_operators(char *input)
{
	int		len;
	int		i;
	char	**matrix;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			len++;
		i++;
	}
	matrix = create_matrix(input, len);
	if (!matrix)
		return (-1);
	if (!validate_operators(matrix))
	{
		free_matrix(matrix);
		return (0);
	}
	free_matrix(matrix);
	return (1);
}

int	input_checker(char *input, t_shell *shell)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (input[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (single_quote || double_quote)
	{
		shell->last_exit = 1;
		update_exit_var(&shell->env_list, ft_itoa(1));
		ft_putstr_fd("minishell: unclosed_quotes\n", 2);
		return (0);
	}
	if (!check_invalid_operators(input))
	{
		shell->last_exit = 2;
		update_exit_var(&shell->env_list, ft_itoa(2));
		return (0);
	}
	return (1);
}

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
