/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:35:31 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/01 14:25:42 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dst;
	char	*source;

	i = 0;
	dst = (char *)dest;
	source = (char *)src;
	if (!n || (dest == NULL && src == NULL))
		return (dest);
	if (dst < source)
	{
		while (i < n)
		{
			dst[i] = source[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			dst[i] = source[i];
	}
	return (dest);
}
/*
int	main(void)
{
	char	src[14];
	char	dest[20];

	strcpy(src, "Hello, world!");

	printf("Prueba básica:\n");
	printf("Contenido de src antes de ft_memmove: %s\n", src);
	ft_memmove(dest, src, strlen(src) + 1);
	printf("Contenido de dest después de ft_memmove: %s\n\n", dest);

	char dest2[20] = "Goodbye";
	printf("Prueba de solapamiento:\n");
	printf("Contenido de dest2 antes de ft_memmove: %s\n", dest2);
	ft_memmove(dest2 + 7, dest2, strlen(dest2) + 1);
	printf("Contenido de dest2 después de ft_memmove: %s\n", dest2);

	return (0);
}*/
