/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

const char	*find_texture_path(const char *base_name)
{
	static char	path[1024];

	ft_strlcpy(path, "./textures/mandatory/", sizeof(path));
	ft_strlcat(path, base_name, sizeof(path));
	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("Error: No se encuentra la textura en: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (NULL);
	}
	return (path);
}
