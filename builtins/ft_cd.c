/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:39:02 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 16:57:30 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_cd(t_shell *shell)
{
	char		*path;
	t_tokens	*current;

	current = shell->tok;
	shell->last_exit = 0;
	if (!current->next || !ft_strcmp(current->next->token, "~"))
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			shell->last_exit = 1;
			return ;
		}
	}
	else
		path = current->next->token;
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n",
			current->next->token);
		shell->last_exit = 1;
		return ;
	}
	return ;
}
