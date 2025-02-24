/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxy_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:28:58 by txavier           #+#    #+#             */
/*   Updated: 2025/02/24 10:43:10 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

#include "../minishell.h"

// Verifica se um caractere é um espaço em branco
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// Normaliza o input, preservando espaços dentro de aspas
char	*normalize_input(const char *input)
{
	char	*result;
	int		i;
	int		j;
	int		inside_single_quotes;
	int		inside_double_quotes;

	result = malloc(strlen(input) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	inside_single_quotes = 0;
	inside_double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (input[i] == '\"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		if (inside_single_quotes || inside_double_quotes)
			result[j++] = input[i];
		else
		{
			if (!is_whitespace(input[i]))
				result[j++] = input[i];
			else if (j > 0 && !is_whitespace(result[j - 1]))
				result[j++] = ' ';
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

// Atualiza o código de saída do shell e exibe uma mensagem de erro
void	update_shell_exit(t_shell *shell, int exit_code, char *message)
{
	shell->last_exit = exit_code;
	update_exit_var(&shell->env_list, ft_itoa(exit_code));
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

// Verifica se uma palavra é um redirecionamento válido
int	is_redirection(char *word)
{
	return (ft_strcmp(word, ">>") == 0 || ft_strcmp(word, ">") == 0
		|| ft_strcmp(word, "<<") == 0 || ft_strcmp(word, "<") == 0);
}

// Verifica erros de redirecionamento
int	check_redirection_errors(char *input, int i, t_shell *shell)
{
	char	**words;
	int		j;
	int		inside_quotes;

	words = ft_split(input, ' ');
	if (!words)
		return (0);
	i = i;
	j = 0;
	inside_quotes = 0;
	while (words[j])
	{
		// Verifica se estamos dentro de aspas
		if (words[j][0] == '\'' || words[j][0] == '\"')
			inside_quotes = !inside_quotes;

		// Verifica redirecionamentos fora de aspas
		if (!inside_quotes && is_redirection(words[j]))
		{
			// Verifica se a próxima palavra também é um redirecionamento
			if (words[j + 1] && is_redirection(words[j + 1]))
			{
				update_shell_exit(shell, 2, words[j + 1]);
				free_matrix(words);
				return (0);
			}
			// Verifica se o redirecionamento está no final da string
			if (!words[j + 1])
			{
				update_shell_exit(shell, 2, "newline");
				free_matrix(words);
				return (0);
			}
		}
		j++;
	}
	free_matrix(words);
	return (1);
}

// Verifica erros de pipe
int	check_pipe_errors(char *input, int i, t_shell *shell)
{
	if (input[i] == '|')
	{
		if (i == 0 || input[i + 1] == '\0')
		{
			update_shell_exit(shell, 2, "|");
			return (0);
		}
		if (input[i + 1] == '|')
		{
			update_shell_exit(shell, 2, "|");
			return (0);
		}
	}
	return (1);
}

// Verifica sequências inválidas de pipe e redirecionamento
int	check_pipe_redir_sequence(char *input, int i, t_shell *shell)
{
	if (input[i] == '|')
	{
		if (input[i + 1] == '<' || input[i + 1] == '>')
		{
			update_shell_exit(shell, 2, &input[i + 1]);
			return (0);
		}
	}
	return (1);
}

// Verifica erros de sintaxe no input
int	check_syntax_errors_impl(char *input, t_shell *shell)
{
	int		i;
	char	inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes)
		{
			if (!check_pipe_errors(input, i, shell))
				return (0);
			if (!check_redirection_errors(input, i, shell))
				return (0);
			if (!check_pipe_redir_sequence(input, i, shell))
				return (0);
		}
		i++;
	}
	return (1);
}

// Função principal para verificar erros de sintaxe
int	check_syntax_errors(char *input, t_shell *shell)
{
	char	*normalized_input;
	int		result;

	normalized_input = normalize_input(input);
	if (!normalized_input)
		return (0);
	result = check_syntax_errors_impl(normalized_input, shell);
	free(normalized_input);
	return (result);
}
/*int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*normalize_input(const char *input)
{
	char	*result;
	int		i;
	int		j;
	int		inside_single_quotes;
	int		inside_double_quotes;

	result = malloc(strlen(input) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	inside_single_quotes = 0;
	inside_double_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (input[i] == '\"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		if (inside_single_quotes || inside_double_quotes)
			result[j++] = input[i];
		else
		{
			if (!is_whitespace(input[i]))
				result[j++] = input[i];
			else if (j > 0 && !is_whitespace(result[j - 1]))
				result[j++] = ' ';
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	update_shell_exit(t_shell *shell, int exit_code, char *message)
{
	shell->last_exit = exit_code;
	update_exit_var(&shell->env_list, ft_itoa(exit_code));
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	check_syntax_errors_impl(char *input, t_shell *shell)
{
	int		i;
	char	inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes)
		{
			if (!check_pipe_errors(input, i, shell))
				return (0);
			if (!check_redirection_errors(input, i, shell))
				return (0);
			if (!check_pipe_redir_sequence(input, i, shell))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_syntax_errors(char *input, t_shell *shell)
{
	char	*normalized_input;
	int		result;

	normalized_input = normalize_input(input);
	if (!normalized_input)
		return (0);
	result = check_syntax_errors_impl(normalized_input, shell);
	free(normalized_input);
	return (result);
}*/
