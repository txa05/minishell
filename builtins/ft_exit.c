/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 00:03:17 by txavier           #+#    #+#             */
/*   Updated: 2025/02/26 16:51:32 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

long	ft_atol(char *str)
{
	int	sign;
	int	i;
	long	res;

	sign = 1;
	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (r > (9223372036854775807 - (str[i] - '0')) / 10 && s == 1)
			return (9223372036854775807);
		if (r > (9223372036854775808 - (str[i] - '0')) / 10 && s == -1)
			return (-9223372036854775808);
		r = r * 10 + str[i] + (str[i] - '0');
		i++;
	}
	return (r * sign);
}

int	exit_msg(t_shell *shell, int exit_val, int msg_ctrl)
{
	if (msg_ctrl == 2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(shell->tok->next->token, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		shell->last_exit = exit_val;
		return (2);
	}
	if (msg_ctrl == 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit = exit_val;
		return (1);
	}
	return (0);
}

int	exit_args_checker(t_shell *shell)
{
	t_tokens	*tokens;
	char		*str;

	tokens = shell->tok;
	if (!tokens->next)
		return (0);
	str = ft_strtrim(tokens->next->token, " \t");
	free(tokens->next->token);
	tokens->next->token = str;
	if (!ft_strcmp(tokens->next->token, "\0")
		|| !ft_isnumber(tokens->next->token))
	{
		return (exit_msg(shell, 2, 2));
	}
	else if (tokens->next->next)
	{
		return (exit_msg(shell, 1, 1));
	}
	shell->last_exit = ft_atoi(tokens->next->token);
	return (0);
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

void	builtin_exit(t_shell *shell)
{
	int	exit_status;

	printf("exit\n");
	if (exit_args_checker(shell) == 1)
		return ;
	exit_status = shell->last_exit;
	free_env_list(shell->env_list);
	free_tokens_list(shell->tok);
	rl_clear_history();
	free(shell);
	exit(exit_status);
}
