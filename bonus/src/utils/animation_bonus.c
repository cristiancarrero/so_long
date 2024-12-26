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

void	update_animation(t_game *game)
{
	game->anim_frame_count++;
	if (game->anim_frame_count % ANIMATION_SPEED == 0)
	{
		game->current_frame = (game->current_frame + 1) % FRAMES_PER_TYPE;
	}
}

static char	*get_enemy_texture_path(int frame)
{
	static char	*paths[ANIMATION_FRAMES] = {
		"./textures/bonus/enemy/enemy1.xpm",
		"./textures/bonus/enemy/enemy2.xpm",
		"./textures/bonus/enemy2/enemy1.xpm",
		"./textures/bonus/enemy2/enemy2.xpm"
	};

	return (paths[frame]);
}

static void	cleanup_loaded_textures(t_game *game, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (game->enemy[i].img)
			mlx_destroy_image(game->mlx, game->enemy[i].img);
		i++;
	}
}

int	load_enemy_textures(t_game *game)
{
	int		i;
	char	*path;

	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		init_img(&game->enemy[i]);
		path = get_enemy_texture_path(i);
		game->enemy[i].img = mlx_xpm_file_to_image(game->mlx, path,
				&game->enemy[i].width, &game->enemy[i].height);
		if (!game->enemy[i].img)
		{
			ft_putstr_fd("Error\nNo se pudo cargar la textura: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\n", 2);
			cleanup_loaded_textures(game, i);
			return (0);
		}
		game->enemy[i].addr = mlx_get_data_addr(game->enemy[i].img,
				&game->enemy[i].bits_per_pixel, &game->enemy[i].line_length,
				&game->enemy[i].endian);
		i++;
	}
	return (1);
}
