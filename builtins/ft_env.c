/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:11:24 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 16:53:55 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_env(t_shell **shell)
{
	t_evar		*current;
	t_tokens	*tokens;

	current = (*shell)->env_list;
	tokens = (*shell)->tok;
	if (tokens->next && tokens->next->token != NULL)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(tokens->next->token, 2);
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
