/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_matrix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 06:21:10 by txavier           #+#    #+#             */
/*   Updated: 2025/02/21 06:36:35 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	count_tokens_nodes(t_tokens *tokens_list)
{
	t_tokens	*current;
	int		i;

	i = 0;
	current = tokens_list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	*converting_nodes_to_array(t_tokens *tokens_list)
{
	char	*array;

	array = NULL;
	if (tokens_list->token != NULL)
		array = ft_strdup(tokens_list->token);
	return (array);
}

char	**generate_tokens_matrix(t_tokens *tokens_list)
{
	int		nbr;
	int		i;
	char	**matrix;

	i = 0;
	nbr = count_tokens_nodes(tokens_list);
	matrix = malloc(sizeof(char *) * (nbr + 1));
	if (!matrix)
		return (NULL);
	while (tokens_list)
	{
		matrix[i] = converting_nodes_to_array(tokens_list);
		i++;
		tokens_list = tokens_list->next;
	}
	matrix[i] = NULL;
	return (matrix);	
}
