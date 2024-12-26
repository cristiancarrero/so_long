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

int	handle_keypress(int keysym, t_game *game)
{
	int	moved;

	moved = 0;
	if (keysym == XK_Escape)
		close_game(game);
	else if (keysym == XK_w || keysym == XK_Up)
		moved = move_player(game, game->player_x, game->player_y - 1);
	else if (keysym == XK_s || keysym == XK_Down)
		moved = move_player(game, game->player_x, game->player_y + 1);
	else if (keysym == XK_a || keysym == XK_Left)
	{
		game->is_facing_left = 1;
		moved = move_player(game, game->player_x - 1, game->player_y);
	}
	else if (keysym == XK_d || keysym == XK_Right)
	{
		game->is_facing_left = 0;
		moved = move_player(game, game->player_x + 1, game->player_y);
	}
	return (moved);
}

int	handle_close(t_game *game)
{
	close_game(game);
	return (0);
}

void	close_game(t_game *game)
{
	ft_putstr_fd("Cerrando juego...\n", 1);
	cleanup_game(game);
	exit(0);
}
