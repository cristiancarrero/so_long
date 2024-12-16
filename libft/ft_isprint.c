/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:19:58 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/18 00:50:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int main(void)
{
    char test_char = 'A';
    
    int result = ft_isprint(test_char);
    
    printf("El carácter %c es imprimible: %d\n", test_char, result);
    
    return 0;
}*/