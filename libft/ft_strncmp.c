/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:24:36 by ccarrero          #+#    #+#             */
/*   Updated: 2024/03/20 15:30:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	*str1 = "Hola";
	char	*str2 = "Hla";

	unsigned int	n = 4;
	int result = ft_strncmp(str1, str2, n);

	if (result == 0)
	{
		write(1, "las cadenas son iguales\n", 22);
	}
	else
	{
	write (1, "las cadenas son diferentes.\n", 25);
	}
	return (0);
}*/
