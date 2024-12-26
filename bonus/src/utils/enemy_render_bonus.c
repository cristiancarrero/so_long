/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_render_array(int rendered[MAX_MAP_HEIGHT][MAX_MAP_WIDTH],
	t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		ft_memset(rendered[i], 0, sizeof(int) * game->map_width);
		i++;
	}
}

static void	set_enemy_params(t_copy_params *params, t_game *game, int i)
{
	params->x = game->enemies[i].x;
	params->y = game->enemies[i].y;
	params->is_player = 0;
	if (game->enemies[i].type == 1)
		params->direction = !game->enemies[i].direction;
	else
		params->direction = game->enemies[i].direction;
	params->img = &game->enemy[game->enemies[i].type * FRAMES_PER_TYPE
		+ game->current_frame];
}

void	render_enemies(t_game *game)
{
	int				i;
	t_copy_params	params;
	int				rendered[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

	if (!game->num_enemies)
		return ;
	init_render_array(rendered, game);
	i = 0;
	while (i < game->num_enemies)
	{
		if (!rendered[game->enemies[i].y][game->enemies[i].x])
		{
			set_enemy_params(&params, game, i);
			if (!params.img || !params.img->img)
				return ;
			copy_image_to_buffer(game, params);
			rendered[game->enemies[i].y][game->enemies[i].x] = 1;
		}
		i++;
	}
}
