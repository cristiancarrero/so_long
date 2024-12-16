/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:37:10 by ccarrero          #+#    #+#             */
/*   Updated: 2024/03/18 12:34:50 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	numero;

	numero = 0;
	while (str[0] != '\0')
	{
		str++;
		numero++;
	}
	return (numero);
}
/*
int	main(void)
{
	char cadena[] = "hello world";
	int numero = ft_strlen(cadena);
	printf("longitud de cadena: %d\n", numero);
	return (0);
}*/
