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
