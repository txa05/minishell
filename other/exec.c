/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchiade-xavier <tchiade-xavier@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:29:40 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 10:43:14 by txavier          ###   ########.fr       */
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

void	close_all(t_exec *exec, t_shell **shell)
{
	dup2(exec->def_r, STDIN_FILENO);
	dup2(exec->def_w, STDOUT_FILENO);
	close(exec->def_r);
	close(exec->def_w);
	wait_for_processes(exec, shell);
}

void	execute_all(char **cmd, t_shell **shell)
{
	t_exec	exec;
	int		i;
	char	**tokens;

	init_execution(&exec);
	i = 0;
	while (cmd[i])
	{
		tokens = malloc(sizeof(char *) * 100);
		tokenize_inputs(cmd[i], tokens);
		if (handle_redirections(tokens, &exec.def_r, &exec.def_w) == -1)
		{
			(*shell)->last_exit = 1;
			free_matrix(tokens);
			break ;
		}
		if (handle_builtin(tokens, shell, &exec) && !cmd[i + 1])
			return ;
		if (cmd[i + 1])
			pipe(exec.fd);
		execute_pipeline(tokens, shell, &exec, cmd[i + 1] != NULL);
		free_matrix(tokens);
		i++;
	}
	close_all(&exec, shell);
}
