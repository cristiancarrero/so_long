/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../libft/libft.h"

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_player = NULL;
	game->img_collect = NULL;
	game->img_exit = NULL;
	game->player.x = 0;
	game->player.y = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->exit_found = 0;
	game->player_found = 0;
	return (1);
}

int	load_game(t_game *game, char *map_path)
{
	ft_putendl_fd("Intentando parsear mapa...", 1);
	if (!parse_map(game, map_path))
	{
		ft_putendl_fd("Error al parsear el mapa", 2);
		return (0);
	}

	ft_putendl_fd("Validando mapa...", 1);
	if (!validate_map(game))
	{
		ft_putendl_fd("Error al validar el mapa", 2);
		return (0);
	}

	ft_putendl_fd("Creando ventana...", 1);
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, WINDOW_TITLE);
	if (!game->win)
	{
		ft_putendl_fd("Error al crear la ventana", 2);
		return (0);
	}

	ft_putendl_fd("Cargando imágenes...", 1);
	if (!load_images(game))
	{
		ft_putendl_fd("Error al cargar imágenes", 2);
		mlx_destroy_window(game->mlx, game->win);
		return (0);
	}

	render_game(game);
	return (1);
}