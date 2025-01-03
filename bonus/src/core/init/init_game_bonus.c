/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

static void	init_buffer(t_game *game)
{
	game->buffer.img = mlx_new_image(game->mlx,
			game->map_width * TILE_SIZE, game->map_height * TILE_SIZE);
	if (!game->buffer.img)
	{
		ft_putstr_fd("Error: No se pudo crear el buffer\n", 2);
		return ;
	}
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length,
			&game->buffer.endian);
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;
}

static int	init_mlx_components(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error: No se pudo inicializar MLX\n", 2);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		ft_putstr_fd("Error: No se pudo crear la ventana\n", 2);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
		return (0);
	}
	init_buffer(game);
	return (1);
}

int	init_game(t_game *game, char *map_path)
{
	init_game_values(game);
	if (!read_map(map_path, game))
	{
		ft_putstr_fd("Error: No se pudo leer el mapa\n", 2);
		return (0);
	}
	if (!validate_map(game))
	{
		cleanup_map(game->map);
		game->map = NULL;
		return (0);
	}
	if (!init_mlx_components(game) || !load_textures(game))
	{
		cleanup_game(game);
		return (0);
	}
	init_enemies(game);
	init_hud(game);
	return (1);
}
