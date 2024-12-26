/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_game_values(t_game *game)
{
	game->moves = 0;
	game->collected = 0;
	game->collectibles = 0;
	game->is_facing_left = 0;
	game->frame_count = 0;
	game->enemy_move_count = 0;
	game->anim_frame_count = 0;
	game->current_frame = 0;
}

void	init_player(t_game *game)
{
	game->player_x = 0;
	game->player_y = 0;
}
