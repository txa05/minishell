/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:02:33 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 06:46:37 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"	

char	*handle_home_directory(char *cmd, t_shell *shell)
{
	char	*home;
	char	*full_path;

	home = ft_getenv("HOME", shell);
	if (!home)
		return (NULL);
	full_path = ft_strjoin(home, cmd + 1);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*handle_absolute_or_relative_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

void	print_directory_error(char *cmd_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free(cmd_path);
}

void	execute_command(t_shell *shell, char *cmd_path)
{
	char	**env_matrix;
	char	**args;

	env_matrix = generate_matrix(shell->env_list);
	args = generate_tokens_matrix(shell->tok);
	if (execve(cmd_path, args, env_matrix) == -1)
	{
		cmd_exec_error(2, NULL);
		free_env_list(shell->env_list);
		exit(1);
	}
}

void	execute_extern_command(t_shell *shell)
{
	char		*cmd_path;
	struct stat	st;

	shell->last_exit = 0;
	if (!shell->tok)
	{
		cmd_exec_error(1, NULL);
		free_env_list(shell->env_list);
		exit(127);
	}
	cmd_path = search_cmd(shell->tok->token, shell);
	if (!cmd_path)
	{
		cmd_exec_error(1, shell->tok->token);
		free_env_list(shell->env_list);
		exit(127);
	}
	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_directory_error(cmd_path);
		free_env_list(shell->env_list);
		exit(126);
	}
	execute_command(shell, cmd_path);
}
