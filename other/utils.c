/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:36:33 by txavier           #+#    #+#             */
/*   Updated: 2025/02/22 16:08:19 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	free_tokens_list(t_tokens *list)
{
	t_tokens	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->token)
			free(temp->token);
		temp->token = NULL;
		if (temp)
			free(temp);
		temp = NULL;
	}
	list = NULL;
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		if (tokens)
		{
			free(tokens[i]);
			i++;
		}
	}
	free(tokens);
	tokens = NULL;
}
