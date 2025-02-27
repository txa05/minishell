/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:33:29 by txavier           #+#    #+#             */
/*   Updated: 2025/02/11 14:28:47 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	handle_simple_builtin(t_shell **shell, t_exec *exec)
{
	t_tokens	*tok;

	tok = (*shell)->tok;
	if (!tok || !tok->token)
		return (0);
	if (is_builtin(tok->token))
	{
		exec_builtin(shell);
		dup2(exec->def_r, STDIN_FILENO);
		dup2(exec->def_w, STDOUT_FILENO);
		close(exec->def_r);
		close(exec->def_w);
		return (1);
	}
	return (0);
}

void	update_exit_var(t_evar **env, char *value)
{
	t_evar	*current;

	current = *env;
	while (current)
	{
		if (!ft_strcmp(current->name, "?"))
		{
			free(current->value);
			current->value = ft_strdup(value);
			free(value);
			return ;
		}
		current = current->next;
	}
}

void	child_process(t_shell **shell, t_exec *exec, int has_pipe)
{
	t_tokens	*tok;

	tok = (*shell)->tok;
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
	if (tok != NULL && is_builtin(tok->token))
		exec_builtin(shell);
	else
		execute_extern_command(*shell);
	free_tokens_list((*shell)->tok);
	free_env_list((*shell)->env_list);
	exit((*shell)->last_exit);
}

void	execute_pipeline(t_shell **shell, t_exec *exec, int has_next)
{
	signal(SIGINT, handle_cat_ctrl_c);
	exec->pid = fork();
	if (exec->pid == 0)
	{
		child_process(shell, exec, has_next);
	}
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
	{
		if (WIFEXITED(exec->status))
			(*shell)->last_exit = WEXITSTATUS(exec->status);
		if (WIFSIGNALED(exec->status) && WTERMSIG(exec->status) == SIGINT)
			(*shell)->last_exit = 130;
	}
	update_exit_var(&(*shell)->env_list, ft_itoa((*shell)->last_exit));
}
