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
	if (input[0] != NULL && !ft_strncmp("-n", input[i], 2))
	{
		new_line_flag = 0;
		i++;
	}
	while (input[i] != NULL)
	{
		printf("%s", input[i]);
		if (input[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (new_line_flag)
		printf("\n");
}
