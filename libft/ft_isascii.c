/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:22:28 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/18 00:55:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int main(void)
{
    char test_char = 'A';
    if (ft_isascii(test_char))
        printf("%c es un carácter ASCII.\n", test_char);
    else
        printf("%c no es un carácter ASCII.\n", test_char);
    return 0;
}*/