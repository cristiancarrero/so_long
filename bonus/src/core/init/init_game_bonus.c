/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		print_error("Error initializing MLX");
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		print_error("Error creating window");
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

static void	init_buffer(t_game *game)
{
	game->buffer.img = mlx_new_image(game->mlx,
			game->map_width * TILE_SIZE, game->map_height * TILE_SIZE);
	if (!game->buffer.img)
	{
		print_error("Error creating buffer");
		return ;
	}
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length,
			&game->buffer.endian);
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;
}

static void	count_map_enemies(t_game *game)
{
	int	i;
	int	j;

	game->num_enemies = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'M')
				game->num_enemies++;
			j++;
		}
		i++;
	}
}

int	init_game(t_game *game, char *map_path)
{
	if (!game)
		return (0);
	init_game_values(game);
	if (!read_map(map_path, game))
		return (0);
	if (!validate_map(game))
	{
		cleanup_map(game->map);
		return (0);
	}
	init_window(game);
	if (!game->mlx || !game->win)
		return (0);
	init_buffer(game);
	init_player(game);
	if (!load_textures(game))
	{
		cleanup_game(game);
		return (0);
	}
	count_map_enemies(game);
	init_enemies(game);
	init_hud(game);
	return (1);
}
