/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:17:11 by txavier           #+#    #+#             */
/*   Updated: 2025/02/08 17:50:28 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	heredoc_term(char **tokens, int i)
{
	free(tokens[i]);
	free(tokens[i + 1]);
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
}

int	execute_redirect(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], ">"))
		{
			if (handle_simple_output_redirection(tokens, i) == -1)
				return (-1);
		}
		else if (!ft_strcmp(tokens[i], ">>"))
		{
			if (handle_double_output_redirection(tokens, i) == -1)
				return (-1);
		}
		else if (!ft_strcmp(tokens[i], "<"))
			return (handle_input_redirection(tokens, i));
		else if (!ft_strcmp(tokens[i], "<<"))
			return (handle_heredoc(tokens, i));
		i++;
	}
	return (0);
}
