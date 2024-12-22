/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

void	render_map(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->mlx || !game->win)
		return ;
	mlx_clear_window(game->mlx, game->win);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			render_tile(game, x, y);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.img, 0, 0);
	render_hud(game);
}

int	render_frame(t_game *game)
{
	render_map(game);
	return (0);
}
