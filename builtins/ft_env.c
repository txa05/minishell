/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:11:24 by txavier           #+#    #+#             */
/*   Updated: 2025/01/22 21:27:34 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_env(t_shell **shell, char **tokens)
{
	t_evar	*current;

	current = (*shell)->env_list;
	if (tokens[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(tokens[1], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		(*shell)->last_exit = 127;
		update_exit_var(&(*shell)->env_list, ft_itoa(127));
	}
	else
	{
		while (current)
		{
			if (current->value && ft_strcmp(current->name, "?"))
				printf("%s=%s\n", current->name, current->value);
			current = current->next;
		}
		(*shell)->last_exit = 0;
	}
}
