/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:26:56 by txavier           #+#    #+#             */
/*   Updated: 2025/01/15 12:32:49 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	cwd[1024];

	shell->last_exit = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_putstr_fd("minishell: pwd", 2);
		shell->last_exit = 1;
	}
	printf("%s\n", cwd);
	return ;
}
