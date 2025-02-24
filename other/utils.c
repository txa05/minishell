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

int	is_valid_env(const char *key)
{
	int	i;

	i = 0;
	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	while (key[i])
	{
		if (ft_isalnum(key[i]) && key[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
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
	if (tokens)
		free(tokens);
	tokens = NULL;
}
