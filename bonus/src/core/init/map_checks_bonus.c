/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_top_bottom_walls(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[y][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

static int	check_side_walls(t_game *game, int y)
{
	if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		return (0);
	return (1);
}

int	check_walls(t_game *game)
{
	int	y;

	if (!check_top_bottom_walls(game, 0))
		return (0);
	y = 1;
	while (y < game->map_height - 1)
	{
		if (!check_side_walls(game, y))
			return (0);
		y++;
	}
	if (!check_top_bottom_walls(game, game->map_height - 1))
		return (0);
	return (1);
}
