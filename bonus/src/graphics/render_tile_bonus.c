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

void	render_tile(t_game *game, int x, int y)
{
	t_copy_params	params;

	params.x = x;
	params.y = y;
	params.is_player = 0;
	params.direction = 0;

	// Primero renderizamos el suelo en todas las casillas
	params.img = &game->floor;
	copy_image_to_buffer(game, params);

	// Luego renderizamos el contenido específico de la casilla
	if (game->map[y][x] == '1')
	{
		params.img = &game->wall;
		copy_image_to_buffer(game, params);
	}
	else if (game->map[y][x] == 'C' || game->map[y][x] == 'n' || game->map[y][x] == 'N')
	{
		// Si hay un coleccionable o un enemigo sobre un coleccionable, dibujamos el coleccionable
		if (game->map[y][x] == 'C' || game->map[y][x] == 'n')
		{
			params.img = &game->collect;
			copy_image_to_buffer(game, params);
		}
		// Si hay un enemigo (N o n), dibujamos el enemigo
		if (game->map[y][x] == 'N' || game->map[y][x] == 'n')
		{
			int i = 0;
			while (i < game->num_enemies)
			{
				if (game->enemies[i].x == x && game->enemies[i].y == y)
				{
					params.direction = game->enemies[i].direction;
					params.img = &game->enemy[game->current_frame];
					copy_image_to_buffer(game, params);
					break;
				}
				i++;
			}
		}
	}
	else if (game->map[y][x] == 'E')
	{
		params.img = &game->exit;
		copy_image_to_buffer(game, params);
	}
	else if (game->map[y][x] == 'P')
	{
		params.is_player = 1;
		params.img = game->is_facing_left ? &game->player_left : &game->player;
		copy_image_to_buffer(game, params);
	}
}
