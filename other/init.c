/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:26:26 by txavier           #+#    #+#             */
/*   Updated: 2025/02/22 11:52:28 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	init_program(t_shell **shell, char **env)
{
	*shell = malloc(sizeof(t_shell));
	(*shell)->last_exit = 0;
	fill_env_list(env, &(*shell)->env_list);
	(*shell)->tok = NULL;
}

void	init_execution(t_exec *exec)
{
	exec->prev_fd = 0;
	exec->status = 0;
	exec->def_w = 1;
	exec->def_r = 0;
	signal(SIGINT, SIG_IGN);
}

void	handle_cat_ctrl_c(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	handle_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_sigs(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
