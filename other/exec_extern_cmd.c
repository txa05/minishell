/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:02:33 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 11:05:45 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*find_exec(char **dirs, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	temp = NULL;
	full_path = NULL;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(char *str, t_shell *shell)
{
	t_evar	*current;

	current = shell->env_list;
	while (current)
	{
		if (!ft_strcmp(str, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}	

char	*search_cmd(char *cmd, t_shell *shell)
{
	char	*full_path;
	char	**dirs;
	char	*path;

	path = ft_getenv("PATH", shell);
	if (path == NULL)
		return (NULL);
	if (cmd[0] == '/' || !ft_strncmp(cmd, ".", 1))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	dirs = ft_split(path, ':');
	full_path = find_exec(dirs, cmd);
	free_matrix(dirs);
	return (full_path);
}

void	cmd_exec_error(int i, char *str)
{
	if (i == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found", 2);
		write(2, "\n", 1);
	}
	else
		ft_putstr_fd("execve", 2);
}

void	execute_extern_command(char **tokens, t_shell *shell)
{
	char	*cmd_path;
	char	**env_matrix;

	shell->last_exit = 0;
	cmd_path = search_cmd(tokens[0], shell);
	if (!cmd_path)
	{
		cmd_exec_error(1, tokens[0]);
		free_matrix(tokens);
		free_env_list(shell->env_list);
		exit(127);
	}
	env_matrix = generate_matrix(shell->env_list);
	if (execve(cmd_path, tokens, env_matrix) == -1)
	{
		cmd_exec_error(2, NULL);
		free_env_list(shell->env_list);
		free_matrix(env_matrix);
		free_matrix(tokens);
		exit(1);
	}
}
