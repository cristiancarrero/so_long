/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:49:12 by ccarrero          #+#    #+#             */
/*   Updated: 2024/03/20 22:10:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len >= needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	*haystack = "Hello, World!";
	const char	*needle = "World";
	size_t	len = strlen(haystack);

	char	*result = ft_strnstr(haystack, needle, len);
	if (result != NULL)
	{
		printf("'%s' encontrado en '%s' en la posición %lld\n", needle,
			haystack, result - haystack);
	}
	else
	{
		printf("'%s' no encontrado en '%s'\n", needle, haystack);
	}
	return (0);
}*/
