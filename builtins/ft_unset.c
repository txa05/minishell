/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:02:09 by txavier           #+#    #+#             */
/*   Updated: 2025/01/23 14:59:48 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	remove_env_var(char *var, t_shell *shell)
{
	t_evar	*current;
	t_evar	*prev;

	shell->last_exit = 0;
	current = shell->env_list;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->name, var) && ft_strcmp(var, "?"))
		{
			if (prev)
				prev->next = current->next;
			else
				shell->env_list = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
}

void	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[1])
		return ;
	while (args[i])
	{
		remove_env_var(args[i], shell);
		i++;
	}
	return ;
}
