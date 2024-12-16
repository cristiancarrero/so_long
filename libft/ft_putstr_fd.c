/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:06:31 by ccarrero          #+#    #+#             */
/*   Updated: 2024/04/02 16:07:12 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *str, int fd)
{
	if (fd < 0)
		return ;
	if (str == NULL)
		return ;
	while (str[0] != '\0')
	{
		write(fd, str, 1);
		str++;
	}
}
/*
int	main(void)
{
	ft_putstr_fd("lets go", 1);
	return (0);
}*/
