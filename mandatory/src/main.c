/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	init_vars(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->moves = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->is_facing_left = 0;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_error("No se pudo inicializar MLX");
		exit(1);
	}
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE,
			"So Long");
	if (!game->win)
	{
		print_error("No se pudo crear la ventana");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_error("Uso: ./so_long <mapa.ber>");
		return (1);
	}
	init_vars(&game);
	if (!parse_map(argv[1], &game))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!validate_map(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		print_error("No se pudo inicializar MLX");
		cleanup_game(&game);
		return (1);
	}
	if (!load_textures(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	game.win = mlx_new_window(game.mlx,
			game.map_width * TILE_SIZE,
			game.map_height * TILE_SIZE,
			"So Long");
	if (!game.win)
	{
		print_error("No se pudo crear la ventana");
		cleanup_game(&game);
		return (1);
	}
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_window_close, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}
