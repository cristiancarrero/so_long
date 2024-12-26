/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	try_texture_path(char *path, const char *base_path, const char *name)
{
	ft_strlcpy(path, base_path, 1024);
	ft_strlcat(path, name, 1024);
	ft_putstr_fd("Intentando acceder a: ", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
}

const char	*find_texture_path(const char *base_name)
{
	static char	path[1024];
	const char	*paths[] = {
		"./textures/bonus/",
		"./textures/mandatory/",
		"./bonus/textures/",
		NULL
	};
	int			i;

	i = 0;
	while (paths[i])
	{
		try_texture_path(path, paths[i], base_name);
		if (access(path, F_OK) == 0)
		{
			ft_putstr_fd("Textura encontrada en: ", 1);
			ft_putstr_fd(path, 1);
			ft_putstr_fd("\n", 1);
			return (path);
		}
		i++;
	}
	ft_putstr_fd("Error: No se encuentra la textura en ninguna ruta: ", 1);
	ft_putstr_fd(base_name, 1);
	ft_putstr_fd("\n", 1);
	return (NULL);
}
