/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchiade-xavier <tchiade-xavier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:29:40 by txavier           #+#    #+#             */
/*   Updated: 2025/02/11 15:11:58 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix != NULL)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

void	close_all(t_exec *exec, t_shell **shell)
{
	dup2(exec->def_r, STDIN_FILENO);
	close(exec->def_r);
	dup2(exec->def_w, STDOUT_FILENO);
	close(exec->def_w);
	wait_for_processes(exec, shell);
}

void	process_command_execution(char **cmd, t_shell **shell,
			t_exec *exec, int i)
{
	tokenize(cmd[i], &(*shell)->tok);
	if (i == 0
		&& handle_redirections(*shell, &exec->def_r, &exec->def_w) == -1)
	{
		free_tokens_list((*shell)->tok);
		(*shell)->tok = NULL;
		(*shell)->last_exit = 1;
		update_exit_var(&(*shell)->env_list, ft_itoa(1));
		return ;
	}
	if (!cmd[i + 1] && handle_simple_builtin(shell, exec))
	{
		free_tokens_list((*shell)->tok);
		(*shell)->tok = NULL;
		return ;
	}
	if (cmd[i + 1])
		pipe(exec->fd);
	execute_pipeline(shell, exec, cmd[i + 1] != NULL);
	free_tokens_list((*shell)->tok);
	(*shell)->tok = NULL;
}

void	execute_all(char **cmd, t_shell **shell)
{
	t_exec	exec;
	int		i;

	init_execution(&exec);
	i = 0;
	while (cmd[i])
	{
		process_command_execution(cmd, shell, &exec, i);
		i++;
	}
	close_all(&exec, shell);
}
