/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:48:16 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/02 18:08:18 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
int	main(void)
{
	char	uppercase;
	char	lowercase;

	uppercase = 'H';
	lowercase = ft_tolower(uppercase);
	printf("Uppercase: %c\nLowercase: %c\n", uppercase, lowercase);
	return (0);
}*/
