/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:17:38 by txavier           #+#    #+#             */
/*   Updated: 2025/02/23 00:57:07 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	is_redirect(char token)
{
	if (token == '>')
		return (1);
	else if ((token == '<'))
		return (1);
	else
		return (0);
}

int	read_check(char	*line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}
