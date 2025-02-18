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
	t_exec		exec;
	int			i;
	int			flag;
	char		**tokens;
	char		*fixed_input;

	init_execution(&exec);
	i = 0;
	flag = 0;
	fixed_input = NULL;
	while (cmd[i])
	{
		tokens = malloc(sizeof(char *) * 100);
		fixed_input = reorder_input(cmd[i]);
		tokenize_inputs(fixed_input, tokens, &flag);
		free(fixed_input);
		if (handle_redirections(tokens, &exec.def_r, &exec.def_w, &flag) == -1)
		{
			(*shell)->last_exit = 1;
			update_exit_var(&(*shell)->env_list, ft_itoa(1));
			free_matrix(tokens);
			break ;
		}
		if (!cmd[i + 1] && handle_builtin(tokens, shell, &exec))
		{
			free_matrix(tokens);
			return ;
		}
		if (cmd[i + 1])
			pipe(exec.fd);
		execute_pipeline(tokens, shell, &exec, cmd[i + 1] != NULL);
		free_matrix(tokens);
		i++;
	}
	close_all(&exec, shell);
}
