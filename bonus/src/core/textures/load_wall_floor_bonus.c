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

static int	init_wall_texture(t_game *game)
{
	char	*path;

	init_img(&game->wall);
	path = (char *)find_texture_path("wall");
	if (!path)
	{
		ft_putstr_fd("Error\nNo se encontró la textura del muro\n", 2);
		return (0);
	}
	game->wall.img = mlx_xpm_file_to_image(game->mlx, path,
			&game->wall.width, &game->wall.height);
	if (!game->wall.img)
	{
		ft_putstr_fd("Error\nNo se pudo cargar la textura: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	game->wall.addr = mlx_get_data_addr(game->wall.img,
			&game->wall.bits_per_pixel,
			&game->wall.line_length,
			&game->wall.endian);
	return (1);
}

static int	init_floor_texture(t_game *game)
{
	char	*path;

	init_img(&game->floor);
	path = (char *)find_texture_path("floor");
	if (!path)
	{
		ft_putstr_fd("Error\nNo se encontró la textura del suelo\n", 2);
		return (0);
	}
	game->floor.img = mlx_xpm_file_to_image(game->mlx, path,
			&game->floor.width, &game->floor.height);
	if (!game->floor.img)
	{
		ft_putstr_fd("Error\nNo se pudo cargar la textura: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	game->floor.addr = mlx_get_data_addr(game->floor.img,
			&game->floor.bits_per_pixel,
			&game->floor.line_length,
			&game->floor.endian);
	return (1);
}

int	load_wall_floor_textures(t_game *game)
{
	if (!init_wall_texture(game))
	{
		return (0);
	}
	if (!init_floor_texture(game))
	{
		if (game->wall.img)
			mlx_destroy_image(game->mlx, game->wall.img);
		return (0);
	}
	return (1);
}
