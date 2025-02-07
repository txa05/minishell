/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txavier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:00:43 by txavier           #+#    #+#             */
/*   Updated: 2024/05/15 16:51:41 by txavier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dest);
}
/*int	main(void)
{
	char	src[] = "Tchiade Xavier";
	char	dest[50];
	size_t	t = 5;

	ft_memcpy(dest, src, t);
	printf("string original: %s\n", src);
	printf("string copiada: %s\n", dest);
}*/
