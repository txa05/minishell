/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:01:03 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 08:13:17 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

char	*extract_variable(char *input, size_t *i)
{
	size_t	var_len;
	char	*var_start;
	char	*var_name;

	var_start = &input[*i + 1];
	var_len = 0;
	while (var_start[var_len] && (ft_isalnum(var_start[var_len])
			|| var_start[var_len] == '_' || var_start[var_len] == '?'))
		var_len++;
	var_name = ft_substr(var_start, 0, var_len);
	*i += var_len + 1;
	return (var_name);
}

char	*expand_variable(char *result, char *var_name, t_shell *shell)
{
	char	*var_value;
	char	*temp;

	var_value = get_value(var_name, shell);
	free(var_name);
	temp = ft_strjoin_free(result, var_value, 1);
	ft_free(&var_value);
	return (temp);
}

char	*append_char(char *result, char c)
{
	char	current_char[2];
	char	*temp;

	current_char[0] = c;
	current_char[1] = '\0';
	temp = ft_strjoin_free(result, current_char, 1);
	return (temp);
}

char	*expand_vars(char *input, t_shell *shell)
{
	char	*result;
	size_t	i;
	int		in_single_quote;
	int		in_double_quote;

	if (!input)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		handle_quotes(input[i], &in_single_quote, &in_double_quote);
		if (input[i] == '$' && input[i + 1] && !in_single_quote
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'
				|| input[i + 1] == '?'))
			result = expand_variable(result,
					extract_variable(input, &i), shell);
		else
			result = append_char(result, input[i++]);
	}
	return (result);
}
