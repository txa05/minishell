/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:33:29 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 12:41:01 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	init_execution(t_exec *exec)
{
	exec->prev_fd = 0;
	exec->status = 0;
	exec->def_w = 0;
	exec->def_r = 0;
	signal(SIGINT, SIG_IGN);
}

int	handle_builtin(char **tokens, t_shell **shell, t_exec *exec)
{
	if (is_builtin(tokens[0]))
	{
		exec_builtin(tokens, shell);
		dup2(exec->def_r, STDIN_FILENO);
		dup2(exec->def_w, STDOUT_FILENO);
		close(exec->def_r);
		close(exec->def_w);
		return (1);
	}
	return (0);
}

void	child_process(char **tokens, t_shell **shell,
		t_exec *exec, int has_pipe)
{
	signal(SIGINT, SIG_DFL);
	if (exec->prev_fd)
	{
		dup2(exec->prev_fd, STDIN_FILENO);
		close(exec->prev_fd);
	}
	if (has_pipe)
	{
		dup2(exec->fd[1], STDOUT_FILENO);
		close(exec->fd[1]);
		close(exec->fd[0]);
	}
	if (is_builtin(tokens[0]))
		exec_builtin(tokens, shell);
	else
		execute_extern_command(tokens, *shell);
	free_matrix(tokens);
	free_env_list((*shell)->env_list);
	exit((*shell)->last_exit);
}

void	execute_pipeline(char **tokens, t_shell **shell,
		t_exec *exec, int has_next)
{
	exec->pid = fork();
	if (exec->pid == 0)
		child_process(tokens, shell, exec, has_next);
	if (exec->prev_fd != 0)
		close(exec->prev_fd);
	if (has_next)
	{
		close(exec->fd[1]);
		exec->prev_fd = exec->fd[0];
	}
	else
		exec->prev_fd = 0;
}

void	wait_for_processes(t_exec *exec, t_shell **shell)
{
	while (waitpid(-1, &exec->status, 0) > 0)
		;
	if (WIFEXITED(exec->status))
		(*shell)->last_exit = WEXITSTATUS(exec->status);
	if (WIFSIGNALED(exec->status) && WTERMSIG(exec->status) == SIGINT)
		(*shell)->last_exit = 130;
	update_exit_var(&(*shell)->env_list, ft_itoa((*shell)->last_exit));
	signal(SIGINT, handle_ctrl_c);
}
