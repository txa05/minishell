/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:59:19 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 05:47:04 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

t_tokens	*new_token(char *token, int quote_flag)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->token = token;
	new->quote_flag = quote_flag;
	new->next = NULL;
	return (new);
}

void	add_token(t_tokens **list, char *token, int quote_flag)
{
	t_tokens	*new;
	t_tokens	*temp;

	temp = NULL;
	new = new_token(token, quote_flag);
	if (!(*list))
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	handle_word(char *input, int i, t_tokens **head, int *quote_flag)
{
	char	*token;

	token = NULL;
	while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			i = handle_quoted_part(input, i, &token, quote_flag);
		}
		else
		{
			i = handle_normal_part(input, i, &token);
		}
	}
	if (*token)
	{
		add_token(head, token, *quote_flag);
	}
	return (i);
}

char	*ft_strncpy(char *dest, char *src, int i)
{
	int	j;

	j = 0;
	if (!src)
		return (dest);
	while (i > 0 && src[j] != '\0')
	{
		dest[j] = src[j];
		j++;
		i--;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strcat(char *s1, char *s2)
{
	int	s1_len;
	int	s2_len;
	int	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	i = 0;
	if (!s2)
		return (s1);
	while (i < s2_len)
	{
		s1[s1_len++] = s2[i];
		i++;
	}
	s1[s1_len] = '\0';
	return (s1);
}
