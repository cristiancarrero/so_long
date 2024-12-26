/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	load_player_textures(t_game *game)
{
	game->textures.player_right = load_texture(game,
			"textures/player_right.xpm");
	game->textures.player_left = load_texture(game,
			"textures/player_left.xpm");
	game->textures.player_up = load_texture(game,
			"textures/player_up.xpm");
	game->textures.player_down = load_texture(game,
			"textures/player_down.xpm");
}

static void	load_map_textures(t_game *game)
{
	game->textures.wall = load_texture(game, "textures/wall.xpm");
	game->textures.floor = load_texture(game, "textures/floor.xpm");
	game->textures.collectible = load_texture(game,
			"textures/collectible.xpm");
	game->textures.exit = load_texture(game, "textures/exit.xpm");
}

void	init_textures(t_game *game)
{
	load_player_textures(game);
	load_map_textures(game);
}
