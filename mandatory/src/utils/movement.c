/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static int	handle_move_to_exit(t_game *game)
{
	if (game->collected == game->collectibles)
	{
		ft_putstr_fd("¡Has ganado!\n", 1);
		close_game(game);
	}
	else
	{
		ft_putstr_fd("Faltan coleccionables: ", 1);
		ft_putnbr_fd(game->collectibles - game->collected, 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	char	next_pos;

	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	next_pos = game->map[new_y][new_x];
	if (next_pos == '1')
		return (0);
	if (next_pos == 'E')
		return (handle_move_to_exit(game));
	if (next_pos == 'C')
	{
		game->collected++;
		ft_putstr_fd("Coleccionable recogido. Total: ", 1);
		ft_putnbr_fd(game->collected, 1);
		ft_putstr_fd("/", 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putstr_fd("\n", 1);
	}
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	return (1);
}
