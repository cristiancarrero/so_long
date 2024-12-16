/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:50:48 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/18 01:12:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int main(void)
{
    char src[] = "Hello, world!";
    char dest1[20];
    char dest2[20];

    ft_memcpy(dest1, src, strlen(src) + 1);
    printf("Resultado usando ft_memcpy: %s\n", dest1);

    memcpy(dest2, src, strlen(src) + 1);
    printf("Resultado usando memcpy: %s\n", dest2);

    return 0;
}*/