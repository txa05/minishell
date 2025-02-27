/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:59:01 by txavier           #+#    #+#             */
/*   Updated: 2025/02/27 16:31:14 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	check_overflow(char c, long res, int *status, int sign)
{
	if (res > (9223372036854775807 - (c - '0')) / 10 && sign == 1)
	{
		*status = 1;
		return (1);
	}
	if ((unsigned long)res > ((unsigned long)9223372036854775807 + 1
			- (c - '0')) / 10 && sign == -1)
	{
		*status = 1;
		return (1);
	}
	return (0);
}

long	ft_atol(char *str, int *status)
{
	int		sign;
	int		i;
	long	res;

	sign = 1;
	i = 0;
	res = 0;
	*status = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_overflow(str[i], res, status, sign))
			return (2);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
