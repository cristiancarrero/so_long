/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE,
			"so_long");
	if (!game->win)
		return (0);
	game->buffer.img = mlx_new_image(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE);
	if (!game->buffer.img)
		return (0);
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length,
			&game->buffer.endian);
	if (!game->buffer.addr)
		return (0);
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;
	if (!load_textures(game))
		return (0);
	return (1);
}
