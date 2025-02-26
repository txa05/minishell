/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:23:25 by txavier           #+#    #+#             */
/*   Updated: 2025/02/26 17:31:49 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdio.h"
#include "unistd.h"

long    ft_atol(char *str, int *status)
{
    int     sign;
    int     i;
    long    res;

    sign = 1;
    i = 0;
    res = 0;
    *status = 0; // Inicializa o status como "sucesso"

    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        if (res > (9223372036854775807 - (str[i] - '0')) / 10 && sign == 1)
        {
            *status = 1; // Indica overflow
            return (2);
        }
        if (res > ((unsigned long)9223372036854775807 + 1 - (str[i] - '0')) / 10 && sign == -1)
        {
            *status = 1; // Indica underflow
            return (2);
        }
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

int	main(void)
{
	char	str[] = "9223372036854775808";
	int	status = 0;
	long	res;

	res = ft_atol(str, &status);
	if (!status)
		printf("-->> res = %ld\n", res);
	else
		printf("the value is bigger than a long\n");
	return (0);
}
