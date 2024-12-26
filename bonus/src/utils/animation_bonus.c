/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	get_next_frame(int current_frame)
{
	int	type;
	int	frame_in_type;

	type = current_frame / FRAMES_PER_TYPE;
	frame_in_type = current_frame % FRAMES_PER_TYPE;
	frame_in_type = (frame_in_type + 1) % FRAMES_PER_TYPE;
	return (type * FRAMES_PER_TYPE + frame_in_type);
}

void	update_animation(t_game *game)
{
	if (!game)
		return ;
	game->frame_count++;
	if (game->frame_count >= ANIMATION_SPEED)
	{
		game->frame_count = 0;
		game->current_frame = get_next_frame(game->current_frame);
	}
}
