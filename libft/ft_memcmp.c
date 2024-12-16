/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:48:32 by ccarrero          #+#    #+#             */
/*   Updated: 2024/03/14 13:48:38 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	str1[] = "Hello";
	char	str2[] = "Hello";
	int		result;

	result = ft_memcmp(str1, str2, 5);
	if (result == 0)
	{
		printf("Los bloques de memoria son iguales.\n");
	}
	else if (result < 0)
	{
		printf("la  memoria s1 es menor que el bloque de memoria s2.\n");
	}
	else
	{
		printf("la memoria s1 es mayor que el bloque de memoria s2.\n");
	}
	return (0);
}*/
