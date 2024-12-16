/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:46:23 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 23:46:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	if (!s || !f)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	result = (char *)malloc((i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char toupper_wrapper(unsigned int index, char c)
{
    (void)index;
    if (c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

int main(void)
{
    char *str = "hello world";
    char *result = ft_strmapi(str, toupper_wrapper);
    if (result)
    {
        printf("Original: %s\n", str);
        printf("Modified: %s\n", result);
        free(result);
    }
    else
    {
        printf("Error: No se pudo aplicar la función ft_strmapi.\n");
    }
    return 0;
}*/