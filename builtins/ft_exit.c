/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:03:17 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 03:03:41 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	exit_args_checker(char **args, t_shell *shell)
{
	char	*str;

	str = ft_strtrim(args[1], " \t");
	free(args[1]);
	args[1] = str;
	if (!ft_strcmp(args[1], "\0") || !ft_isnumber(args[1]))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->last_exit = 2;
	}
	else if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->last_exit = 1;
	}
	else
	{
		printf("exit\n");
		shell->last_exit = ft_atoi(args[1]);
	}
}

void	exit_program(t_shell *shell)
{
	int	exit_code;

	exit_code = shell->last_exit;
	ft_putstr_fd("exit\n", 1);
	free_env_list(shell->env_list);
	rl_clear_history();
	free(shell);
	exit(exit_code);
}

void	builtin_exit(char **args, t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
		exit_args_checker(args, shell);
	else
		printf("exit\n");
	exit_code = shell->last_exit;
	free_env_list(shell->env_list);
	rl_clear_history();
	free(shell);
	free_tokens(args);
	exit(exit_code);
}
