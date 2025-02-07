/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanion_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 07:29:54 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 07:33:24 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*get_value(char *key, t_shell *shell)
{
	t_evar	*current;

	current = shell->env_list;
	while (current)
	{
		if (!ft_strcmp(current->name, key))
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	if (free_s1 && s1)
		free(s1);
	return (res);
}

void	ft_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
