/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:17:42 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/17 21:52:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include "libft.h"

static int	check_overflow(long long int n, int sign, int digit)
{
	if (sign == 1 && (n > LLONG_MAX / 10 || \
		(n == LLONG_MAX / 10 && digit > LLONG_MAX % 10)))
		return (-1);
	if (sign == -1 && (n < LLONG_MIN / 10 || \
		(n == LLONG_MIN / 10 && digit > -(LLONG_MIN % 10))))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long int	n;
	int				sign;

	n = 0;
	sign = 1;
	while (*str && ((*str > 8 && *str < 14) || (*str == 32)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ((*str >= '0' && *str <= '9')))
	{
		if (!check_overflow(n, sign, (*str - '0')))
			return (check_overflow(n, sign, (*str - '0')));
		n = n * 10 + sign * (*str - '0');
		str++;
	}
	return ((int)n);
}
/*
int main(void)
{
    const char *test_string = "1234567890";
    
    int mine = ft_atoi(test_string);
    int theirs = atoi(test_string);
    
    printf("Resultado de ft_atoi: %d\n", mine);
    printf("Resultado de atoi: %d\n", theirs);
    
    return 0;
}*/
