/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:42:57 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/18 00:49:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int main(void)
{
    char test_char = '5';
    
    int result = ft_isdigit(test_char);
    
    printf("El carácter %c es un dígito: %d\n", test_char, result);
    
    return 0;
}*/