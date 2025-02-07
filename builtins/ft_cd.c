/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:39:02 by txavier           #+#    #+#             */
/*   Updated: 2025/01/15 13:04:40 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_cd(char **args, t_shell *shell)
{
	char	*path;

	shell->last_exit = 0;
	if (!args[1])
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
		path = args[1];
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
		shell->last_exit = 1;
		return ;
	}
	return ;
}
