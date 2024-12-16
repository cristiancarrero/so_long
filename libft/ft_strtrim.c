/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:00:21 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 19:00:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	end = start + ft_strlen(s1);
	while (*start && ft_isset(*start, set))
		++start;
	while (start < end && ft_isset(*(end - 1), set))
		--end;
	ret = ft_substr(start, 0, end - start);
	return (ret);
}
/*
int	main(void)
{
	char const *s1 = "  \t\t Hello, World! \t\t  ";
	char const *set = " \t";

	char *trimmed_str = ft_strtrim(s1, set);
	if (trimmed_str)
	{
		printf("Cadena original: \"%s\"\n", s1);
		printf("Conjunto de caracteres a eliminar: \"%s\"\n", set);
		printf("Cadena después de eliminar caracteres de inicio y fin: \"%s\"\n",
			trimmed_str);

		free(trimmed_str);
	}
	else
	{
		printf("La función ft_strtrim devolvió NULL.\n");
	}

	return (0);
}*/