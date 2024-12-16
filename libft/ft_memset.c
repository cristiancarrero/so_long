/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:50:32 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/02 13:42:13 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = (unsigned char *)str;
	while (i < n)
	{
		*p = (unsigned char)c;
		p++;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[50];

	ft_memset(str, 'A', 10);
	printf("Resultado de ft_memset: %s\n", str);
	memset(str, 0, sizeof(str));
	memset(str, 'A', 10);
	printf("Resultado de memset: %s\n", str);
	if (strcmp(str, "AAAAAAAAAA") == 0)
	{
		printf("Los resultados son iguales.\n");
	}
	else
	{
		printf("Los resultados son diferentes.\n");
	}
	return (0);
}
*/