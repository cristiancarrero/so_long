/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static void	render_floor(t_game *game, int x, int y)
{
	t_copy_params	params;

	params.x = x;
	params.y = y;
	params.is_player = 0;
	params.img = &game->floor;
	copy_image_to_buffer(game, params);
}

static void	render_object(t_game *game, int x, int y, char tile)
{
	t_copy_params	params;

	params.x = x;
	params.y = y;
	params.is_player = (tile == 'P');
	if (tile == '1')
		params.img = &game->wall;
	else if (tile == 'P')
		params.img = &game->player;
	else if (tile == 'C')
		params.img = &game->collect;
	else if (tile == 'E')
		params.img = &game->exit;
	else
		return ;
	copy_image_to_buffer(game, params);
}

void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	render_floor(game, x, y);
	render_object(game, x, y, tile);
}
