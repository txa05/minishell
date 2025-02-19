/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:17:11 by txavier           #+#    #+#             */
/*   Updated: 2025/02/11 14:33:16 by txavier          ###   ########.fr       */
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

void	execute_redirect(char **tokens, int *flag, int *check)
{
	int	i;
	int	flag2;

	i = 0;
	flag2 = *flag;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (flag2)
			{
				flag2 -= 1;
				i++;
				continue ;
			}
		}
		if (!ft_strcmp(tokens[i], "<"))
		{
			handle_input_redirection(tokens, i, check);
		}	
		i++;
	}
	i = 0;
	flag2 = *flag;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (flag2)
			{
				flag2 -= 1;
				i++;
				continue ;
			}
		}
		if (!ft_strcmp(tokens[i], ">") && !*flag)
			handle_simple_output_redirection(tokens, i);
		else if (!ft_strcmp(tokens[i], ">>") && !*flag)
			handle_double_output_redirection(tokens, i);
		else if (!ft_strcmp(tokens[i], "<<") && !*flag)
			handle_heredoc(tokens, i);
		if (tokens[i] && !ft_strcmp(">", tokens[i]))
			*flag -= 1;
		i++;
	}
}
