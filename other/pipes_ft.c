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

char	*ft_getenv(char *str, t_shell *shell)
{
	t_evar	*current;

	current = shell->env_list;
	while (current)
	{
		if (!ft_strcmp(str, current->name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return (s1);
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**allocate_commands(int count)
{
	char	**result;

	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (result);
}

void	split_pipes(char *input, char ***commands)
{
	int		count;
	char	**result;

	count = count_commands(input);
	result = allocate_commands(count);
	split_into_commands(input, result);
	*commands = result;
}
