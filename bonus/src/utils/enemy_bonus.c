/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_enemies(t_game *game)
{
	int	x;
	int	y;
	int	enemy_count;

	ft_putstr_fd("\n=== Inicializando enemigos ===\n", 1);
	
	if (game->num_enemies == 0)
	{
		ft_putstr_fd("No hay enemigos para inicializar\n", 1);
		return;
	}

	if (game->num_enemies > MAX_ENEMIES)
	{
		ft_putstr_fd("Advertencia: Demasiados enemigos. Limitando a ", 1);
		ft_putnbr_fd(MAX_ENEMIES, 1);
		ft_putstr_fd("\n", 1);
		game->num_enemies = MAX_ENEMIES;
	}

	// Inicializar enemigos
	enemy_count = 0;
	y = 0;
	while (y < game->map_height && enemy_count < game->num_enemies)
	{
		x = 0;
		while (x < game->map_width && enemy_count < game->num_enemies)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'M')
			{
				ft_putstr_fd("Inicializando enemigo en posición: ", 1);
				ft_putnbr_fd(x, 1);
				ft_putstr_fd(",", 1);
				ft_putnbr_fd(y, 1);
				ft_putstr_fd(" de tipo: ", 1);
				// El tipo se determina por el carácter en el mapa
				int type = (game->map[y][x] == 'M') ? 1 : 0;
				ft_putnbr_fd(type, 1);
				ft_putstr_fd("\n", 1);

				game->enemies[enemy_count].x = x;
				game->enemies[enemy_count].y = y;
				// Los enemigos tipo 2 empiezan mirando a la izquierda (dirección 1)
				game->enemies[enemy_count].direction = type ? 1 : 0;
				game->enemies[enemy_count].frame = 0;
				game->enemies[enemy_count].type = type;
				enemy_count++;
			}
			x++;
		}
		y++;
	}

	ft_putstr_fd("Total de enemigos inicializados: ", 1);
	ft_putnbr_fd(enemy_count, 1);
	ft_putstr_fd("\n=== Inicialización de enemigos completada ===\n\n", 1);
}

static int	check_enemy_at_position(t_game *game, int x, int y, int current_enemy)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (i != current_enemy && 
			game->enemies[i].x == x && 
			game->enemies[i].y == y)
		{
			ft_putstr_fd("Colisión entre enemigos evitada en posición: ", 1);
			ft_putnbr_fd(x, 1);
			ft_putstr_fd(",", 1);
			ft_putnbr_fd(y, 1);
			ft_putstr_fd("\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	update_enemies(t_game *game)
{
	int		i;
	int		new_x;
	int		new_y;
	char	next_tile;
	char	current_tile;

	if (game->frame_count % ENEMY_MOVE_INTERVAL != 0)
	{
		game->frame_count++;
		return;
	}

	i = 0;
	while (i < game->num_enemies)
	{
		new_x = game->enemies[i].x;
		new_y = game->enemies[i].y;

		// Determinar la nueva posición basada en la dirección
		if (game->enemies[i].direction == 0)
			new_x++;
		else
			new_x--;

		next_tile = game->map[new_y][new_x];
		current_tile = game->map[game->enemies[i].y][game->enemies[i].x];
		
		// Comprobar colisión con el jugador
		if (next_tile == 'P')
		{
			ft_putstr_fd("¡Has sido atrapado por un enemigo! Fin del juego.\n", 1);
			close_game(game);
			exit(0);
		}
		
		// Comprobar si el movimiento es válido
		if (new_x >= 0 && new_x < game->map_width &&
			next_tile != '1' && next_tile != 'E' &&
			!check_enemy_at_position(game, new_x, new_y, i))
		{
			// Actualizar la posición anterior
			if (current_tile == 'N' || current_tile == 'M' || 
				current_tile == 'n' || current_tile == 'm')
			{
				game->map[game->enemies[i].y][game->enemies[i].x] = 
					(current_tile == 'n' || current_tile == 'm') ? 'C' : '0';
			}

			// Mover el enemigo
			game->enemies[i].x = new_x;
			
			// Actualizar la nueva posición con el carácter correcto según el tipo
			if (next_tile == 'C')
				game->map[new_y][new_x] = game->enemies[i].type ? 'm' : 'n';
			else
				game->map[new_y][new_x] = game->enemies[i].type ? 'M' : 'N';
		}
		else
		{
			// Cambiar dirección si hay obstáculo
			game->enemies[i].direction = !game->enemies[i].direction;
		}
		i++;
	}
	game->frame_count++;
}

void	render_enemies(t_game *game)
{
	int				i;
	t_copy_params	params;
	int				rendered[MAX_MAP_HEIGHT][MAX_MAP_WIDTH];

	if (!game->num_enemies)
		return ;

	// Inicializar array de control de renderizado
	for (int y = 0; y < game->map_height; y++)
		for (int x = 0; x < game->map_width; x++)
			rendered[y][x] = 0;

	i = 0;
	while (i < game->num_enemies)
	{
		int x = game->enemies[i].x;
		int y = game->enemies[i].y;

		// Solo renderizar si no hay otro enemigo ya renderizado en esa posición
		if (!rendered[y][x])
		{
			params.x = x;
			params.y = y;
			params.is_player = 0;
			// Para el tipo 2, invertimos la dirección para que coincida con el sprite
			params.direction = game->enemies[i].type ? !game->enemies[i].direction : game->enemies[i].direction;
			
			// Calculamos el frame actual basado en el tipo de enemigo y el frame de animación
			int frame_offset = game->enemies[i].type * FRAMES_PER_TYPE;
			int current_frame = frame_offset + game->current_frame;

			params.img = &game->enemy[current_frame];

			if (!params.img || !params.img->img)
			{
				ft_putstr_fd("Error: Textura de enemigo no válida\n", 1);
				return ;
			}

			copy_image_to_buffer(game, params);
			rendered[y][x] = 1;
		}
		i++;
	}
}

int	check_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	if (!game->num_enemies)
		return (0);

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
		{
			ft_putstr_fd("¡Has chocado con un enemigo! Fin del juego.\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
} 