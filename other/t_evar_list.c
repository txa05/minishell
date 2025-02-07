/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_evar_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 05:46:39 by txavier           #+#    #+#             */
/*   Updated: 2025/02/02 06:39:04 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_env_list(t_evar *list)
{
	t_evar	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

t_evar	*creat_env_node(char *env)
{
	t_evar	*new_node;
	size_t	len;

	new_node = malloc(sizeof(t_evar));
	if (!new_node)
		return (NULL);
	len = ft_strcspn(env, "=");
	new_node->name = ft_substr(env, 0, len);
	new_node->value = ft_strdup(env + len + 1);
	new_node->next = NULL;
	return (new_node);
}

void	add_to_list(t_evar **list, t_evar *new_node)
{
	t_evar	*current;

	if (!*list)
		*list = new_node;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	add_exit_control_var(t_evar **list)
{
	t_evar	*new_node;
	t_evar	*current;

	new_node = malloc (sizeof(t_evar));
	if (!new_node)
		return ;
	new_node->name = ft_strdup("?");
	new_node->value = ft_strdup("0");
	new_node->next = NULL;
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	fill_env_list(char **env, t_evar **list)
{
	int		i;
	t_evar	*new_node;

	i = 0;
	*list = NULL;
	while (env[i])
	{
		new_node = creat_env_node(env[i]);
		if (!new_node)
			return ;
		add_to_list(list, new_node);
		i++;
	}
	add_exit_control_var(list);
}
