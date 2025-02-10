/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:11:23 by txavier           #+#    #+#             */
/*   Updated: 2025/01/15 12:26:39 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	is_valid_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-' && str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] && str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	ft_echo(char **input, t_shell *shell)
{
	int	i;
	int	new_line_flag;

	new_line_flag = 1;
	i = 1;
	shell->last_exit = 0;
	if (!input[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (input[i] && is_valid_flag(input[i]))
	{
		new_line_flag = 0;
		i++;
	}
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (new_line_flag)
		printf("\n");
}
