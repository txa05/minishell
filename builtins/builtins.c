/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:23:08 by txavier           #+#    #+#             */
/*   Updated: 2025/01/26 17:56:49 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_builtin(char *cmd)
{
	if (*cmd && !ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

void	exec_builtin(char **tokens, t_shell **shell)
{
	if (!ft_strcmp(tokens[0], "cd"))
		ft_cd(tokens, *shell);
	else if (!ft_strcmp(tokens[0], "echo"))
		ft_echo(tokens, *shell);
	else if (!ft_strcmp(tokens[0], "pwd"))
		ft_pwd(*shell);
	else if (!ft_strcmp(tokens[0], "env"))
		ft_env(shell, tokens);
	else if (!ft_strcmp(tokens[0], "export"))
		ft_export(tokens, *shell);
	else if (!ft_strcmp(tokens[0], "unset"))
		ft_unset(tokens, *shell);
	else if (!ft_strcmp(tokens[0], "exit"))
		builtin_exit(tokens, *shell);
	update_exit_var((&(*shell)->env_list), ft_itoa((*shell)->last_exit));
}
