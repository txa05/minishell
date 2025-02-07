/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:19:44 by txavier           #+#    #+#             */
/*   Updated: 2024/05/17 10:58:55 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}
//int main() {
//const char *test1 = "42";
//const char *test2 = "    -42";
//const char *test3 = "4193 with words";
//const char *test4 = "words and 987";
//const char *test5 = "-91283472332";
//printf("ft_atoi(\"%s\") = %d\n", test1, ft_atoi(test1)); // Espera-se: 42
//printf("ft_atoi(\"%s\") = %d\n", test2, ft_atoi(test2)); // Espera-se: -42
//printf("ft_atoi(\"%s\") = %d\n", test3, ft_atoi(test3)); // Espera-se: 419
//printf("ft_atoi(\"%s\") = %d\n", test4, ft_atoi(test4)); // Espera-se: 0
//printf("ft_atoi(\"%s\") = %d\n", test5, ft_atoi(test5)); 
//return 0;
//}
