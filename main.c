/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:58:03 by txavier           #+#    #+#             */
/*   Updated: 2025/02/06 23:45:14 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	g_sig;

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	g_sig = 0;
	(void)ac;
	(void)av;
	init_program(&shell, envp);
	main_loop(shell);
	exit_program(shell);
	return (0);
}
