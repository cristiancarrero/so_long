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
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->is_facing_left = 0;
	init_img(&game->player);
	init_img(&game->wall);
	init_img(&game->floor);
	init_img(&game->collect);
	init_img(&game->exit);
	init_img(&game->buffer);
}

static int	check_args_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
	{
		print_error("El mapa debe tener extensión .ber");
		return (0);
	}
	return (1);
}

static int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Uso: ./so_long <mapa.ber>");
		return (0);
	}
	return (check_args_extension(argv[1]));
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_args(argc, argv))
		return (1);
	init_vars(&game);
	if (!init_game(&game, argv[1]))
	{
		cleanup_game(&game);
		return (1);
	}
	if (!init_mlx(&game))
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
