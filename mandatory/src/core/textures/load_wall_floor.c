/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_wall_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

static int	load_wall(t_game *game)
{
	const char	*wall_path;

	wall_path = find_texture_path("wall.xpm");
	if (!wall_path)
		return (0);
	game->wall.img = mlx_xpm_file_to_image(game->mlx,
			(char *)wall_path,
			&game->wall.width,
			&game->wall.height);
	if (!game->wall.img)
		return (0);
	game->wall.addr = mlx_get_data_addr(game->wall.img,
			&game->wall.bits_per_pixel,
			&game->wall.line_length,
			&game->wall.endian);
	if (!game->wall.addr)
		return (0);
	return (1);
}

static int	load_floor(t_game *game)
{
	const char	*floor_path;

	floor_path = find_texture_path("floor.xpm");
	if (!floor_path)
		return (0);
	game->floor.img = mlx_xpm_file_to_image(game->mlx,
			(char *)floor_path,
			&game->floor.width,
			&game->floor.height);
	if (!game->floor.img)
		return (0);
	game->floor.addr = mlx_get_data_addr(game->floor.img,
			&game->floor.bits_per_pixel,
			&game->floor.line_length,
			&game->floor.endian);
	if (!game->floor.addr)
		return (0);
	return (1);
}

int	load_wall_floor_textures(t_game *game)
{
	if (!load_wall(game))
		return (0);
	if (!load_floor(game))
		return (0);
	return (1);
}
