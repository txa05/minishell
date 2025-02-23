/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern_cmd_aux.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:11:10 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 13:42:46 by txavier          ###   ########.fr       */
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

char	*search_in_path(char *cmd, t_shell *shell)
{
	char	*path;
	char	**dirs;
	path = ft_getenv("PATH", shell);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	path = find_exec(dirs, cmd);
	free_matrix(dirs);
	return (path);
}

void	cmd_exec_error(int i, char *str)
{
	if (!str)
		return ;
	if (i == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
		ft_putstr_fd("execve", 2);
}

int	is_absolute_or_relative_path(char *cmd)
{
	if (cmd[0] == '/')
		return (1);
	else if (!ft_strncmp(cmd, "./", 2))
		return (1);
	else if (!ft_strncmp(cmd, "../", 3))
		return (1);
	return (0);
}

char	*search_cmd(char *cmd, t_shell *shell)
{
	if (!cmd || *cmd == '\0')
		return (NULL);
	if (cmd[0] == '\0')
		return (handle_home_directory(cmd, shell));
	if (is_absolute_or_relative_path(cmd))
		return (handle_absolute_or_relative_path(cmd));
	return (search_in_path(cmd, shell));
}
