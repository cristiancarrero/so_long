/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:32:56 by ccarrero          #+#    #+#             */
/*   Updated: 2024/05/19 01:30:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstring;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	newstring = (char *)malloc((len + 1) * sizeof(char));
	if (!newstring)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstring[i] = s[start + i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
/*
int	main(void)
{
	char	*original;

	original = "Esta es una cadena de ejemplo";
	unsigned int start = 5;
	size_t len = 10;

	char *subcadena = ft_substr(original, start, len);

	if (subcadena)
	{
		printf("Subcadena: %s\n", subcadena);
		free(subcadena);
	}
	else
	{
		printf("Error al crear la subcadena\n");
	}
	return (0);
}
*/
