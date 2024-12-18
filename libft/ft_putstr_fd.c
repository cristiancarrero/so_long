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

void	ft_putstr_fd(const char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}
/*
int	main(void)
{
	ft_putstr_fd("lets go", 1);
	return (0);
}*/
