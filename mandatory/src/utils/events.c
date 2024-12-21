/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static int	move_player(t_game *game, int new_x, int new_y)
{
	char	next_pos;

	next_pos = game->map[new_y][new_x];
	if (next_pos == '1')
		return (0);
	if (next_pos == 'C')
		game->collected++;
	if (next_pos == 'E' && game->collected == game->collectibles)
	{
		game->moves++;
		ft_putstr_fd("¡Has ganado!\n", 1);
		close_game(game);
		return (1);
	}
	if (next_pos == 'E')
		return (0);
	game->map[game->player_pos.y][game->player_pos.x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_pos.x = new_x;
	game->player_pos.y = new_y;
	game->moves++;
	return (1);
}

int	handle_keypress(int keycode, t_game *game)
{
	int	moved;

	moved = 0;
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		moved = move_player(game, game->player_pos.x, game->player_pos.y - 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		moved = move_player(game, game->player_pos.x, game->player_pos.y + 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		game->is_facing_left = 1;
		moved = move_player(game, game->player_pos.x - 1, game->player_pos.y);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		game->is_facing_left = 0;
		moved = move_player(game, game->player_pos.x + 1, game->player_pos.y);
	}
	if (moved)
		render_map(game);
	return (0);
}

int	handle_window_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
