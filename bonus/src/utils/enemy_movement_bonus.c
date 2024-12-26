/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_enemy_at_position(t_game *game, int x, int y, int current)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (i != current && game->enemies[i].x == x && game->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

static void	handle_enemy_collision(t_game *game)
{
	ft_putstr_fd("¡Has sido atrapado por un enemigo!\n", 1);
	close_game(game);
	exit(0);
}

static void	process_enemy(t_game *game, int i)
{
	int	new_x;
	int	new_y;

	if (game->enemies[i].direction == 0)
		new_x = game->enemies[i].x + 1;
	else
		new_x = game->enemies[i].x - 1;
	new_y = game->enemies[i].y;
	if (game->map[new_y][new_x] == 'P')
		handle_enemy_collision(game);
	if (new_x >= 0 && new_x < game->map_width
		&& game->map[new_y][new_x] != '1'
		&& game->map[new_y][new_x] != 'E'
		&& !check_enemy_at_position(game, new_x, new_y, i))
		update_enemy_position(game, i, new_x, new_y);
	else
		game->enemies[i].direction = !game->enemies[i].direction;
}

void	update_enemies(t_game *game)
{
	int	i;

	if (game->enemy_move_count % ENEMY_MOVE_INTERVAL != 0)
	{
		game->enemy_move_count++;
		return ;
	}
	i = 0;
	while (i < game->num_enemies)
	{
		process_enemy(game, i);
		i++;
	}
	game->enemy_move_count++;
}
