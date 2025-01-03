/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_enemy_textures_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	load_enemy_frame(t_game *game, int frame)
{
	char	*path;

	path = get_enemy_path(frame);
	if (!path)
		return (0);
	if (!create_enemy_image(game, frame, path))
		return (0);
	return (1);
}

static void	cleanup_loaded_frames(t_game *game, int last_frame)
{
	int	i;

	i = 0;
	while (i < last_frame)
	{
		if (game->enemy[i].img)
			mlx_destroy_image(game->mlx, game->enemy[i].img);
		i++;
	}
}

int	load_enemy_textures(t_game *game)
{
	int	frame;

	frame = 0;
	while (frame < ANIMATION_FRAMES)
	{
		if (!load_enemy_frame(game, frame))
		{
			cleanup_loaded_frames(game, frame);
			return (0);
		}
		frame++;
	}
	return (1);
}
