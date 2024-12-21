/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_bonus.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	// Primero comprobar colisión con muros
	if (game->map[new_y][new_x] == WALL)
		return;

	int old_x = game->player.x;
	int old_y = game->player.y;

	// Comprobar colisión con enemigos
	for (int i = 0; i < game->num_enemies; i++)
	{
		if (new_x == game->enemies[i].pos.x && new_y == game->enemies[i].pos.y)
		{
			game->state = STATE_LOSE;
			render_game(game);
			mlx_do_sync(game->mlx);
			usleep(1000000);
			close_window(game);
			return;
		}
	}

	// Comprobar coleccionables
	if (game->map[new_y][new_x] == COLLECT)
	{
		game->collected++;
		game->map[new_y][new_x] = EMPTY;
	}

	// Comprobar salida
	if (game->map[new_y][new_x] == EXIT)
	{
		if (game->collected == game->collectibles)
		{
			game->moves++;
			game->state = STATE_VICTORY;
			game->map[old_y][old_x] = EMPTY;
			game->player.x = new_x;
			game->player.y = new_y;
			render_game(game);
			mlx_do_sync(game->mlx);
			usleep(500000);
			close_window(game);
			return;
		}
		return;
	}

	// Actualizar el mapa
	game->map[old_y][old_x] = EMPTY;
	game->map[new_y][new_x] = PLAYER;

	// Actualizar la posición del jugador
	game->player.x = new_x;
	game->player.y = new_y;
	game->moves++;

	// Actualizar la dirección del jugador para la animación
	if (new_x < old_x)
		game->player.direction = -1;
	else if (new_x > old_x)
		game->player.direction = 1;

	render_game(game);
}

int	check_collision(t_game *game, int x, int y)
{
	// Comprobar límites del mapa
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (1);

	// Comprobar colisión con muros
	if (game->map[y][x] == WALL)
		return (1);

	// Comprobar colisión con enemigos
	for (int i = 0; i < game->num_enemies; i++)
	{
		if (game->enemies[i].active && 
			game->enemies[i].pos.x == x && 
			game->enemies[i].pos.y == y)
		{
			game->state = STATE_LOSE;
			return (1);
		}
	}

	// Comprobar coleccionables
	if (game->map[y][x] == COLLECT)
	{
		game->collected++;
		game->map[y][x] = EMPTY;
		return (0);
	}

	// Comprobar salida
	if (game->map[y][x] == EXIT)
	{
		if (game->collected == game->collectibles)
		{
			game->state = STATE_VICTORY;
			return (0);
		}
		return (1);  // No permitir movimiento a la salida si no has recogido todo
	}

	return (0);  // No hay colisión
} 