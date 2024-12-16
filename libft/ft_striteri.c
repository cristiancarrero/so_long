/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:40:00 by marvin            #+#    #+#             */
/*   Updated: 2024/03/22 00:40:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
/*
void print_index_char(unsigned int index, char *c)
{
    printf("Index: %u, Character: %c\n", index, *c);
}

int main(void)
{
    char str[] = "Hello";

    printf("Original string: %s\n", str);

    ft_striteri(str, print_index_char);

    return 0;
}*/