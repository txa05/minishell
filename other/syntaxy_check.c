/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxy_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:28:58 by txavier           #+#    #+#             */
/*   Updated: 2025/02/24 03:57:48 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
/*
void	update_shel_exit(t_shell *shell, int exit_code, char *message)
{
	shell->last_exit = exit_code;
	update_exit_var(&shell->env_list, ft_itoa(exit_code));
	if (message)
		ft_putstr_fd(message, 2);
}

int check_syntax_errors(char *input, t_shell *shell)
{
    int i = 0;
    int inside_quotes = 0;
    char quote_char = 0;

    // Verifica se a string está vazia ou contém apenas espaços
    if (!input || !*input)
    {
        shell->last_exit = 0;
        update_exit_var(&shell->env_list, ft_itoa(shell->last_exit));
        return (0);
    }

    while (input[i])
    {
        // Verifica aspas
        if ((input[i] == '"' || input[i] == '\'') && (quote_char == 0 || quote_char == input[i]))
        {
            inside_quotes = !inside_quotes;
            if (inside_quotes)
                quote_char = input[i];
            else
                quote_char = 0;
        }

        // Verifica redirecionamentos no fim da linha
        if (!inside_quotes && (input[i] == '>' || input[i] == '<'))
        {
            // Verifica se o redirecionamento está no fim da linha
            if (input[i + 1] == '\0')
            {
                shell->last_exit = 2;
                update_exit_var(&shell->env_list, ft_itoa(shell->last_exit));
                return (1); // Erro de sintaxe
            }

            // Verifica redirecionamentos duplos (>>, <<) ou inválidos (>>>)
            if (input[i + 1] == input[i]) // Caso de >> ou <<
            {
                if (input[i + 2] == input[i]) // Caso de >>> ou <<<
                {
                    shell->last_exit = 2;
                    update_exit_var(&shell->env_list, ft_itoa(shell->last_exit));
                    return (1); // Erro de sintaxe
                }
                i++; // Pula o segundo caractere do redirecionamento
            }
        }

        // Verifica pipe duplo (fora de aspas)
        if (!inside_quotes && input[i] == '|')
        {
            if (input[i + 1] == '|')
            {
                shell->last_exit = 2;
                update_exit_var(&shell->env_list, ft_itoa(shell->last_exit));
                return (1); // Erro de sintaxe
            }
        }

        // Verifica pipe seguido de redirecionamento (fora de aspas)
        if (!inside_quotes && input[i] == '|')
        {
            int j = i + 1;
            while (input[j] == ' ') // Ignora espaços após o pipe
                j++;
            if (input[j] == '>' || input[j] == '<')
            {
                shell->last_exit = 2;
                update_exit_var(&shell->env_list, ft_itoa(shell->last_exit));
                return (1); // Erro de sintaxe
            }
        }

        i++;
    }

    return (0); // Sem erros de sintaxe
}

int	check_syntax_errors(char *input, t_shell *shell)
{
	int		i;
	char	prev = 0;
	char	inside_quotes = 0;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes)
		{
			// Pipe no início, fim ou duplicado
			if (input[i] == '|' && (i == 0 || input[i + 1] == '|' || input[i + 1] == '\0'))
			{
				update_shel_exit(shell, 2, "minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
			// Redirecionamento no fim da string
			if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '\0')
			{
				update_shel_exit(shell, 2, "minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			// Redirecionamento seguido de outro redirecionamento ou pipe
			if ((input[i] == '<' || input[i] == '>') &&
				(prev == '<' || prev == '>' || input[i + 1] == '|' || input[i + 1] == '<' || input[i + 1] == '>'))
			{
				update_shel_exit(shell, 2, "minishell: syntax error near unexpected token\n");
				return (0);
			}
			// Pipe seguido de redirecionamento sem aspas
			if (input[i] == '|' && (input[i + 1] == '<' || input[i + 1] == '>'))
			{
				update_shel_exit(shell, 2, "minishell: syntax error near unexpected token\n");
				return (0);
			}
		}
		prev = input[i];
		i++;
	}
	return (1);
}*/
