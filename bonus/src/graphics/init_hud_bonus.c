/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_hud(t_game *game)
{
	int	width;

	init_img(&game->hud_bg);
	width = game->map_width * TILE_SIZE;
	game->hud_bg.img = mlx_new_image(game->mlx, width, 30);
	if (!game->hud_bg.img)
		print_error("Error creating HUD background");
	game->hud_bg.addr = mlx_get_data_addr(game->hud_bg.img,
			&game->hud_bg.bits_per_pixel,
			&game->hud_bg.line_length,
			&game->hud_bg.endian);
}
