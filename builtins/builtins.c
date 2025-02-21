/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:23:08 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 16:58:06 by txavier          ###   ########.fr       */
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

void	exec_builtin(t_shell **shell)
{
	t_tokens	*tok;

	tok = (*shell)->tok;
	if (!ft_strcmp(tok->token, "cd"))
		ft_cd(*shell);
	else if (!ft_strcmp(tok->token, "echo"))
		ft_echo(*shell);
	else if (!ft_strcmp(tok->token, "pwd"))
		ft_pwd(*shell);
	else if (!ft_strcmp(tok->token, "env"))
		ft_env(shell);
	else if (!ft_strcmp(tok->token, "export"))
		ft_export(*shell);
	else if (!ft_strcmp(tok->token, "unset"))
		ft_unset(*shell);
	else if (!ft_strcmp(tok->token, "exit"))
		builtin_exit(*shell);
	update_exit_var((&(*shell)->env_list), ft_itoa((*shell)->last_exit));
}
