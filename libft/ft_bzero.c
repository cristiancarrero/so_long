/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:35:39 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/17 19:47:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p++ = 0;
		n--;
	}
}
/*
int main(void)
{
    char buffer[10] = "abcdefghi";
    char buffer_ft[10] = "abcdefghi";
    
    printf("Contenido inicial del buffer (ft_bzero): %s\n", buffer_ft);
    ft_bzero(buffer_ft, sizeof(buffer_ft));
    printf("Contenido después de aplicar ft_bzero: %s\n", buffer_ft);
    
    printf("Contenido inicial del buffer (bzero): %s\n", buffer);
    bzero(buffer, sizeof(buffer));
    printf("Contenido después de aplicar bzero: %s\n", buffer);
    
    return 0;
}*/