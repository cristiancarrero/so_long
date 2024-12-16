/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:19:36 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/24 04:15:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *str)
{
	int		i;
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int main(void)
{
    const char *original = "Hello, world!";
    char *duplicate = ft_strdup(original);

    if (duplicate)
    {
        printf("Original string: %s\n", original);
        printf("Duplicate string: %s\n", duplicate);

        free(duplicate);
    }
    else
    {
        printf("Error: No se pudo duplicar la cadena.\n");
    }

    return 0;
}*/