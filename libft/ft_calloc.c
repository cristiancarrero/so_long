/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:18:39 by ccarrero          #+#    #+#             */
/*   Updated: 2024/05/21 00:47:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*buffer;

	if (size != 0 && n > SIZE_MAX / size)
		return (NULL);
	buffer = (void *)malloc(size * n);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, size * n);
	return (buffer);
}
/*
int main(void)
{
    size_t n = 5;
    size_t size = sizeof(int);

    printf("Usando ft_calloc:\n");
    int *ft_buffer = (int *)ft_calloc(n, size);
    if (ft_buffer) {
        printf("Memoria asignada correctamente.\n");
        free(ft_buffer);
        printf("Memoria liberada.\n");
    } else {
        printf("Error al asignar memoria.\n");
    }

    printf("\n");

    printf("Usando calloc:\n");
    int *libc_buffer = (int *)calloc(n, size);
    if (libc_buffer) {
        printf("Memoria asignada correctamente.\n");
        free(libc_buffer);
        printf("Memoria liberada.\n");
    } else {
        printf("Error al asignar memoria.\n");
    }

    return 0;
}*/
