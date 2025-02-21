/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:11:23 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 16:55:58 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	is_valid_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || str[1] == '\0')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	ft_echo(t_shell *shell)
{
	t_tokens	*current;
	int			new_line_flag;

	if (!shell->tok)
		return ;
	current = shell->tok->next;
	new_line_flag = 1;
	shell->last_exit = 0;
	while (current && current->token && is_valid_flag(current->token))
	{
		new_line_flag = 0;
		current = current->next;
	}
	while (current && current->token)
	{
		printf("%s", current->token);
		if (current->next)
			printf(" ");
		current = current->next;
	}
	if (new_line_flag)
		printf("\n");
}
