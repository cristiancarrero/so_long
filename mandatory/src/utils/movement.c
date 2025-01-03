/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static int	handle_move_to_exit(t_game *game)
{
	if (game->collected == game->collectibles)
	{
		ft_putstr_fd("¡Has ganado!\n", 1);
		ft_putstr_fd("Movimientos totales: ", 1);
		ft_putnbr_fd(game->moves, 1);
		ft_putstr_fd("\n", 1);
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

static void	handle_collectible(t_game *game)
{
	game->collected++;
	ft_putstr_fd("Coleccionable recogido. Total: ", 1);
	ft_putnbr_fd(game->collected, 1);
	ft_putstr_fd("/", 1);
	ft_putnbr_fd(game->collectibles, 1);
	ft_putstr_fd("\n", 1);
}

static void	update_position(t_game *game, int new_x, int new_y)
{
	char	current_pos;

	current_pos = game->map[new_y][new_x];
	if (game->map[game->player_y][game->player_x] != 'E')
		game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	if (current_pos == 'E')
		game->map[new_y][new_x] = 'E';
	else
		game->map[new_y][new_x] = 'P';
	game->moves++;
	ft_putstr_fd("Movimientos: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
}

static int	check_move_validity(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	char	next_pos;

	if (!check_move_validity(game, new_x, new_y))
		return (0);
	next_pos = game->map[new_y][new_x];
	if (next_pos == 'E')
	{
		if (game->collected == game->collectibles)
		{
			update_position(game, new_x, new_y);
			return (handle_move_to_exit(game));
		}
		else
		{
			ft_putstr_fd("Faltan coleccionables: ", 1);
			ft_putnbr_fd(game->collectibles - game->collected, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
	}
	if (next_pos == 'C')
		handle_collectible(game);
	update_position(game, new_x, new_y);
	return (1);
}
