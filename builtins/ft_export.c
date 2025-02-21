/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:21:09 by txavier           #+#    #+#             */
/*   Updated: 2025/02/05 19:37:03 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	print_envs(t_shell *shell)
{
	t_evar	*current;

	current = shell->env_list;
	while (current)
	{
		if (!ft_strcmp(current->name, "?"))
			;
		else if (current->value)
			printf("declare -x %s=\"%s\"\n", current->name, current->value);
		else
			printf("declare -x %s\n", current->name);
		current = current->next;
	}
	return ;
}

int	ad_or_updt_envs(char *key, char *value, t_evar **env_list)
{
	t_evar	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			free(key);
			free(value);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	add_or_updt_envs(char *key, char *value, t_evar **env_list)
{
	t_evar	*new_node;

	if (ad_or_updt_envs(key, value, env_list))
		return ;
	else
	{
		new_node = malloc(sizeof(t_evar));
		if (!new_node)
			return ;
		new_node->name = ft_strdup(key);
		if (value)
			new_node->value = ft_strdup(value);
		else
			new_node->value = NULL;
		new_node->next = *env_list;
		*env_list = new_node;
		free(value);
		free(key);
	}
}

void	process_args(char *arg, t_shell *shell)
{
	char	*key;
	char	*value;
	size_t	key_len;

	value = NULL;
	shell->last_exit = 0;
	key_len = ft_strcspn(arg, "=");
	key = ft_substr(arg, 0, key_len);
	if (!is_valid_env(key))
	{
		printf("export: %s: not a valid identifier\n", arg);
		shell->last_exit = 1;
		free(key);
		return ;
	}
	if (arg[key_len] == '=')
		value = ft_strdup(&arg[key_len + 1]);
	add_or_updt_envs(key, value, &shell->env_list);
}

void	ft_export(t_shell *shell)
{
	t_tokens	*tokens;

	tokens = shell->tok;
	if (tokens->next->token == NULL)
	{
		print_envs(shell);
		shell->last_exit = 0;
		return ;
	}
	while (tokens->next)
	{
		process_args(tokens->next->token, shell);
		tokens = tokens->next;
	}
	return ;
}
