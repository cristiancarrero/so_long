/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall_floor_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	load_wall(t_game *game)
{
	const char	*wall_path;

	ft_putstr_fd("Intentando cargar textura de pared...\n", 1);
	wall_path = "./textures/bonus/wall.xpm";
	ft_putstr_fd("Ruta de pared: ", 1);
	ft_putstr_fd((char *)wall_path, 1);
	ft_putstr_fd("\n", 1);
	game->wall.img = mlx_xpm_file_to_image(game->mlx,
			(char *)wall_path,
			&game->wall.width,
			&game->wall.height);
	if (!game->wall.img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen de pared\n", 1);
		return (0);
	}
	game->wall.addr = mlx_get_data_addr(game->wall.img,
			&game->wall.bits_per_pixel,
			&game->wall.line_length,
			&game->wall.endian);
	if (!game->wall.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos de pared\n", 1);
		return (0);
	}
	ft_putstr_fd("Textura de pared cargada con éxito\n", 1);
	return (1);
}

static int	load_floor(t_game *game)
{
	const char	*floor_path;

	ft_putstr_fd("Intentando cargar textura de suelo...\n", 1);
	floor_path = "./textures/bonus/floor.xpm";
	ft_putstr_fd("Ruta de suelo: ", 1);
	ft_putstr_fd((char *)floor_path, 1);
	ft_putstr_fd("\n", 1);
	game->floor.img = mlx_xpm_file_to_image(game->mlx,
			(char *)floor_path,
			&game->floor.width,
			&game->floor.height);
	if (!game->floor.img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen de suelo\n", 1);
		return (0);
	}
	game->floor.addr = mlx_get_data_addr(game->floor.img,
			&game->floor.bits_per_pixel,
			&game->floor.line_length,
			&game->floor.endian);
	if (!game->floor.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos de suelo\n", 1);
		return (0);
	}
	ft_putstr_fd("Textura de suelo cargada con éxito\n", 1);
	return (1);
}

int	load_wall_floor_textures(t_game *game)
{
	ft_putstr_fd("\n=== Cargando texturas de pared y suelo ===\n", 1);
	if (!load_wall(game))
	{
		ft_putstr_fd("Error al cargar la textura de pared\n", 1);
		return (0);
	}
	if (!load_floor(game))
	{
		ft_putstr_fd("Error al cargar la textura de suelo\n", 1);
		return (0);
	}
	ft_putstr_fd("=== Texturas de pared y suelo cargadas con éxito ===\n\n", 1);
	return (1);
}
