/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:51:02 by txavier           #+#    #+#             */
/*   Updated: 2025/01/23 16:08:05 by txavier          ###   ########.fr       */
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

void	split_pipes(char *input, char **commands)
{
	int		i;
	char	*tokens;

	tokens = my_strtok(input, "|");
	i = 0;
	while (tokens)
	{
		commands[i] = tokens;
		tokens = my_strtok(NULL, "|");
		i++;
	}
	commands[i] = NULL;
}
