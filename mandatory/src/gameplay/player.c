/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#           */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	if (!game || !game->map)
		return;

	// Actualizar el mapa primero
	game->map[game->player.y][game->player.x] = EMPTY;

	// Actualizar dirección antes de mover
	if (new_x < game->player.x)
		game->player.direction = -1;
	else if (new_x > game->player.x)
		game->player.direction = 1;

	// Si hay un coleccionable
	if (game->map[new_y][new_x] == COLLECT)
	{
		game->collected++;
		ft_putstr_fd("Coleccionables: ", 1);
		ft_putnbr_fd(game->collected, 1);
		ft_putchar_fd('/', 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putchar_fd('\n', 1);
	}

	// Si llegamos a la salida y tenemos todos los coleccionables
	if (game->map[new_y][new_x] == EXIT && game->collected == game->collectibles)
	{
		game->moves++;
		game->state = STATE_VICTORY;
		render_game(game);
		return;
	}

	// Actualizar posición del jugador
	game->player.x = new_x;
	game->player.y = new_y;
	game->map[new_y][new_x] = PLAYER;
	game->moves++;

	render_game(game);
}

void	init_player(t_game *game)
{
	int	y;
	int	x;

	if (!game || !game->map)
		return ;

	// Encontrar posición inicial del jugador
	game->player.x = -1;
	game->player.y = -1;

	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] == PLAYER)
			{
				game->player.x = x;
				game->player.y = y;
				break ;
			}
		}
		if (game->player.x != -1)
			break ;
	}

	// Inicializar dirección y sprites
	game->player.direction = 1;  // Inicialmente mirando a la derecha
	game->player.sprite_right = game->img_player;  // Sprite original para la derecha
	game->player.sprite_left = NULL;  // Lo crearemos solo cuando sea necesario

	// Crear el sprite volteado
	if (game->img_player)
		game->player.sprite_left = flip_sprite_horizontally(game, game->img_player);
}

int	check_collision(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width ||
		new_y < 0 || new_y >= game->map_height)
		return (1);

	if (game->map[new_y][new_x] == WALL)
		return (1);

	if (game->map[new_y][new_x] == EXIT && game->collected != game->collectibles)
	{
		ft_putstr_fd("¡Necesitas recoger todos los coleccionables! (", 1);
		ft_putnbr_fd(game->collected, 1);
		ft_putchar_fd('/', 1);
		ft_putnbr_fd(game->collectibles, 1);
		ft_putendl_fd(")", 1);
		return (1);
	}

	return (0);
}
  