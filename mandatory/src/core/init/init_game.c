/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

static int	init_game_vars(t_game *game)
{
	game->collected = 0;
	game->moves = 0;
	game->is_facing_left = 0;
	init_img(&game->player);
	init_img(&game->wall);
	init_img(&game->floor);
	init_img(&game->collect);
	init_img(&game->exit);
	init_img(&game->buffer);
	return (1);
}

int	init_game(t_game *game, char *map_path)
{
	game->map = NULL;
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
	if (!init_game_vars(game))
	{
		cleanup_map(game->map);
		game->map = NULL;
		return (0);
	}
	return (1);
}
