/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:18:09 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/01 13:19:35 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>

static int	get_number_length(long long num)
{
	int	length;

	length = 1;
	if (num < 0)
	{
		length++;
		if (num == LLONG_MIN)
		{
			length++;
			num /= 10;
		}
		num = -num;
	}
	while (num >= 10)
	{
		num /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			length;
	long long	num;

	num = n;
	length = get_number_length(num);
	str = (char *)malloc((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[length] = '\0';
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
	}
	else if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--length] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
/*
int main(void)
{
    int number = 12345;
    char *result = ft_itoa(number);
    printf("El número %d convertido a cadena es: %s\n", number, result);
    free(result);
    return 0;
}*/