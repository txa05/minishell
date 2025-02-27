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

int	my_checker(char *input)
{
	if (read_check(input))
	{
		free(input);
		return (0);
	}
	return (1);
}

int	process_input(char *input, t_shell *shell, char **commands)
{
	char	*expanded;

	if (*input)
		add_history(input);
	if (read_check(input))
		return (0);
	if (!validate_syntax(input))
		return (0);
	if (!check_unclosed_quotes(input, shell))
		return (0);
	expanded = expand_vars(input, shell);
	if (!*expanded)
	{
		free(expanded);
		shell->last_exit = 0;
		update_exit_var(&shell->env_list, ft_itoa(0));
		return (1);
	}
	split_pipes(expanded, &commands);
	execute_all(commands, &shell);
	free_matrix(commands);
	free(expanded);
	return (1);
}

void	main_loop(t_shell *shell)
{
	char	*input;
	char	*cmd[70000];

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
		if (process_input(input, shell, cmd) == 0)
		{
			free(input);
			continue ;
		}
		free(input);
	}
}
