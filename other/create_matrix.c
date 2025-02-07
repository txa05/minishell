/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:52:53 by txavier           #+#    #+#             */
/*   Updated: 2025/02/07 10:54:21 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	count_nodes(t_evar *env_list)
{
	t_evar	*current;
	int		i;

	i = 0;
	current = env_list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	*converting_node_to_arr(t_evar *env_list)
{
	char	*entry;
	char	*full_array;

	full_array = NULL;
	entry = ft_strjoin(env_list->name, "=");
	if (!entry)
		return (NULL);
	if (env_list->value)
		full_array = ft_strjoin(entry, env_list->value);
	else
		full_array = ft_strdup(entry);
	free(entry);
	return (full_array);
}

char	**generate_matrix(t_evar *env_list)
{
	int		node_nbr;
	int		i;
	char	**matrix;

	i = 0;
	node_nbr = count_nodes(env_list);
	matrix = malloc(sizeof(char *) * (node_nbr + 1));
	if (!matrix)
		return (NULL);
	while (env_list)
	{
		matrix[i] = converting_node_to_arr(env_list);
		i++;
		env_list = env_list->next;
	}
	matrix[i] = NULL;
	return (matrix);
}
