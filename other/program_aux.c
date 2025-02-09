/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 07:06:23 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 07:17:45 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	init_program(t_shell **shell, char **env)
{
	*shell = malloc(sizeof(t_shell));
	(*shell)->last_exit = 0;
	fill_env_list(env, &(*shell)->env_list);
}

int	process_input(char *input, t_shell *shell, char **commands)
{
	char	*expanded;

	if (*input)
		add_history(input);
	if (read_check(input))
	{
		free(input);
		return (0);
	}
	if (!input_checker(input, shell))
	{
		free(input);
		return (0);
	}
	expanded = expand_vars(input, shell);
	if (!*expanded)
	{
		free(expanded);
		shell->last_exit = 0;
		update_exit_var(&shell->env_list, ft_itoa(0));
		return (1);
	}
	split_pipes(expanded, commands);
	execute_all(commands, &shell);
	free(expanded);
	return (1);
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

void	main_loop(t_shell *shell)
{
	char	*input;
	char	*cmd[100];

	while (18)
	{
		handle_sigs();
		input = readline("minishell$> ");
		if (g_sig == SIGINT)
		{
			shell->last_exit = 130;
			update_exit_var(&shell->env_list, ft_itoa(130));
			g_sig = 0;
		}
		if (!input)
		{
			free(input);
			break ;
		}
		if (!process_input(input, shell, cmd))
			continue ;
		free(input);
	}
}
