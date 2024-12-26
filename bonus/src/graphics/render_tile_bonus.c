/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	render_floor(t_game *game, int x, int y)
{
	t_copy_params	params;

	params.img = &game->floor;
	params.x = x;
	params.y = y;
	params.is_player = 0;
	params.direction = 1;
	copy_image_to_buffer(game, params);
}

static void	render_collectible(t_game *game, int x, int y)
{
	t_copy_params	params;

	params.img = &game->collect;
	params.x = x;
	params.y = y;
	params.is_player = 0;
	params.direction = 1;
	copy_image_to_buffer(game, params);
}

static void	render_player(t_game *game, int x, int y)
{
	t_copy_params	params;

	params.x = x;
	params.y = y;
	params.is_player = 1;
	params.direction = game->is_facing_left;
	if (game->is_facing_left)
		params.img = &game->player_left;
	else
		params.img = &game->player;
	copy_image_to_buffer(game, params);
}

static void	render_wall_or_exit(t_game *game, int x, int y, char tile)
{
	t_copy_params	params;

	params.x = x;
	params.y = y;
	params.is_player = 0;
	params.direction = 1;
	if (tile == '1')
		params.img = &game->wall;
	else
		params.img = &game->exit;
	copy_image_to_buffer(game, params);
}

void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	render_floor(game, x, y);
	if (tile == '1' || tile == 'E')
		render_wall_or_exit(game, x, y, tile);
	else if (tile == 'P')
		render_player(game, x, y);
	else if (tile == 'C')
		render_collectible(game, x, y);
}
