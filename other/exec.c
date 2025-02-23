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

void close_all(t_exec *exec, t_shell **shell)
{
    // Restaura os descritores padrão
    dup2(exec->def_r, STDIN_FILENO);
    close(exec->def_r);
    dup2(exec->def_w, STDOUT_FILENO);
    close(exec->def_w);

    // Espera pelos processos filhos
    wait_for_processes(exec, shell);
}
void execute_all(char **cmd, t_shell **shell)
{
    t_exec exec;
    int i;

    init_execution(&exec);
    i = 0;
    while (cmd[i])
    {
        tokenize(cmd[i], &(*shell)->tok);

        // Aplica redirecionamentos apenas para o primeiro comando
        if (i == 0 && handle_redirections(*shell, &exec.def_r, &exec.def_w) == -1)
        {
            free_tokens_list((*shell)->tok);
            (*shell)->tok = NULL;
            (*shell)->last_exit = 1;
            update_exit_var(&(*shell)->env_list, ft_itoa(1));
            break;
        }

        if (!cmd[i + 1] && handle_simple_builtin(shell, &exec))
        {
            free_tokens_list((*shell)->tok);
            (*shell)->tok = NULL;
            return;
        }

        if (cmd[i + 1])
            pipe(exec.fd);

        execute_pipeline(shell, &exec, cmd[i + 1] != NULL);

        free_tokens_list((*shell)->tok);
        (*shell)->tok = NULL;
        i++;
    }
    close_all(&exec, shell);
}
