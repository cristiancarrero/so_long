/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_tile_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_enemy_tile(t_tile_params *params)
{
	if (params->game->enemies[params->i].type == 1)
	{
		if (params->tile_type == 'C')
			params->game->map[params->y][params->x] = 'm';
		else
			params->game->map[params->y][params->x] = 'M';
	}
	else
	{
		if (params->tile_type == 'C')
			params->game->map[params->y][params->x] = 'n';
		else
			params->game->map[params->y][params->x] = 'N';
	}
}

void	update_enemy_position(t_game *game, int i, int new_x, int new_y)
{
	char			current_tile;
	char			next_tile;
	t_tile_params	params;

	current_tile = game->map[game->enemies[i].y][game->enemies[i].x];
	next_tile = game->map[new_y][new_x];
	if (current_tile == 'N' || current_tile == 'M'
		|| current_tile == 'n' || current_tile == 'm')
	{
		if (current_tile == 'n' || current_tile == 'm')
			game->map[game->enemies[i].y][game->enemies[i].x] = 'C';
		else
			game->map[game->enemies[i].y][game->enemies[i].x] = '0';
	}
	game->enemies[i].x = new_x;
	params = (t_tile_params){game, i, new_x, new_y, next_tile};
	set_enemy_tile(&params);
}
