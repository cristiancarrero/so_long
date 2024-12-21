#include "../../inc/game_bonus.h"
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

// Prototipo de la función de colisión
static int check_enemy_collision(t_game *game, int current_enemy, int x, int y);

// Función para obtener el tiempo actual en milisegundos
static long get_current_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void setup_hooks(t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return;

	// Configurar los hooks básicos
	mlx_hook(game->win, X_EVENT_KEY_PRESS, KeyPressMask, key_press, game);
	mlx_hook(game->win, X_EVENT_EXIT, NoEventMask, close_window, game);
	mlx_loop_hook(game->mlx, (int (*)(void *))game_loop, game);

	// Desactivar autorepetición de teclas
	mlx_do_key_autorepeatoff(game->mlx);
}

int load_next_level(t_game *game)
{
	// Determinar qué mapa acabamos de completar
	char *current_map = game->level_paths[game->current_level - 1];

	// Si acabamos de completar el mapa 3, terminar el juego
	if (ft_strnstr(current_map, "map3.ber", ft_strlen(current_map)))
	{
		ft_putendl_fd("¡Felicidades! ¡Has completado todos los niveles!", 1);
		close_window(game);
		return (0);
	}

	// Si acabamos de completar el mapa 2, cargar el mapa 3
	if (ft_strnstr(current_map, "map2.ber", ft_strlen(current_map)))
	{
		game->current_level = 3;
	}
	// Si acabamos de completar el mapa 1, cargar el mapa 2
	else if (ft_strnstr(current_map, "map1.ber", ft_strlen(current_map)))
	{
		game->current_level = 2;
	}
	else
	{
		ft_putendl_fd("Error: Mapa no reconocido", 2);
		close_window(game);
		return (0);
	}

	// Incrementar el nivel actual
	game->current_level++;

	// Verificar que no nos pasamos del máximo de niveles
	if (game->current_level >= game->max_levels)
	{
		ft_putendl_fd("Error: No hay más niveles disponibles", 2);
		close_window(game);
		return (0);
	}

	// Verificar que el path del siguiente nivel existe
	if (!game->level_paths[game->current_level - 1])
	{
		ft_putendl_fd("Error: No se encontró el siguiente nivel", 2);
		close_window(game);
		return (0);
	}

	// Verificar que el nivel actual es válido
	if (game->current_level < 1 || game->current_level > game->max_levels)
	{
		ft_putendl_fd("Error: Nivel inválido", 2);
		close_window(game);
		return (0);
	}

	// Guardar el estado de MLX antes de limpiar
	void *mlx = game->mlx;

	// Limpiar el nivel actual
	if (game->map)
		free_map(game->map);
	game->map = NULL;

	// Destruir la ventana y recursos actuales
	if (game->win)
	{
		// Primero destruir las imágenes
		if (game->img_wall)
			mlx_destroy_image(game->mlx, game->img_wall);
		if (game->img_floor)
			mlx_destroy_image(game->mlx, game->img_floor);
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
		if (game->img_collect)
			mlx_destroy_image(game->mlx, game->img_collect);
		if (game->img_exit)
			mlx_destroy_image(game->mlx, game->img_exit);

		// Luego destruir la ventana
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
		game->img_wall = NULL;
		game->img_floor = NULL;
		game->img_player = NULL;
		game->img_collect = NULL;
		game->img_exit = NULL;
	}

	// Reiniciar contadores para el nuevo nivel
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->exit_found = 0;
	game->player_found = 0;
	game->enemies = NULL;
	game->num_enemies = 0;

	// Restaurar MLX
	game->mlx = mlx;

	// Cargar el siguiente nivel
	ft_putstr_fd("\nCargando nivel ", 1);
	ft_putnbr_fd(game->current_level, 1);
	ft_putchar_fd('\n', 1);

	if (!load_game(game, game->level_paths[game->current_level - 1]))
	{
		ft_putendl_fd("Error: No se pudo cargar el siguiente nivel", 2);
		close_window(game);
		return (0);
	}

	// Renderizar el nuevo nivel
	render_game(game);

	// Configurar los hooks para la nueva ventana
	setup_hooks(game);

	ft_putendl_fd("=== Carga del siguiente nivel completada ===\n", 1);
	return (1);
}

int	key_press(int keycode, t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return (0);

	if (keycode == KEY_ESC)
		close_window(game);
	else if (game->state == STATE_PLAYING)
	{
		int new_x = game->player.x;
		int new_y = game->player.y;

		if (keycode == KEY_W)
			new_y--;
		else if (keycode == KEY_S)
			new_y++;
		else if (keycode == KEY_A)
			new_x--;
		else if (keycode == KEY_D)
			new_x++;
		else
			return (0);

		move_player(game, new_x, new_y);
		render_game(game);
	}

	return (0);
}

int	window_resize(int width, int height, void *param)
{
	t_game *game;

	game = (t_game *)param;
	if (!game || !game->win)
	{
		ft_putendl_fd("Error: Punteros nulos en window_resize", 2);
		return (0);
	}

	// Limitar dimensiones
	width = (width <= 0) ? game->map_width * TILE_SIZE : width;
	height = (height <= 0) ? game->map_height * TILE_SIZE : height;
	width = (width > MAX_WINDOW_WIDTH) ? MAX_WINDOW_WIDTH : width;
	height = (height > MAX_WINDOW_HEIGHT) ? MAX_WINDOW_HEIGHT : height;

	// Establecer dimensiones mínimas basadas en el mapa
	int min_width = game->map_width * TILE_SIZE / 2;  // Mínimo 50% del tamaño original
	int min_height = game->map_height * TILE_SIZE / 2;

	width = (width < min_width) ? min_width : width;
	height = (height < min_height) ? min_height : height;

	game->window_width = width;
	game->window_height = height;

	render_game(game);
	return (0);
}

int move_enemies(void *param)
{
	t_game *game = (t_game *)param;
	static long last_move = 0;
	long current = get_current_time_ms();
	
	if (current - last_move < 1000)
		return (0);
	last_move = current;

	int mid_height = game->map_height / 2;

	for (int i = 0; i < game->num_enemies; i++)
	{
		if (!game->enemies[i].active)
			continue;

		int next_x = game->enemies[i].pos.x;
		int next_y = game->enemies[i].pos.y;
		int moved = 0;

		// Enemigo tipo X: Movimiento horizontal con cambio vertical
		if (game->enemies[i].type == 1)
		{
			// Si está en movimiento horizontal
			if (game->enemies[i].direction == 0 || game->enemies[i].direction == 1)
			{
				// Moverse a la derecha
				if (game->enemies[i].direction == 0)
				{
					if (game->map[next_y][next_x + 1] != WALL)
					{
						next_x++;
						moved = 1;
					}
					else
					{
						// Al encontrar pared, cambiar a movimiento vertical
						game->enemies[i].direction = 2;  // 2 para subir, 3 para bajar
						if (next_y < mid_height)
							game->enemies[i].direction = 3;  // Bajar si está en la mitad superior
					}
				}
				// Moverse a la izquierda
				else
				{
					if (game->map[next_y][next_x - 1] != WALL)
					{
						next_x--;
						moved = 1;
					}
					else
					{
						// Al encontrar pared, cambiar a movimiento vertical
						game->enemies[i].direction = 2;  // 2 para subir, 3 para bajar
						if (next_y < mid_height)
							game->enemies[i].direction = 3;  // Bajar si está en la mitad superior
					}
				}
			}
			// Si está en movimiento vertical
			else
			{
				static int steps = 0;
				// Subir
				if (game->enemies[i].direction == 2)
				{
					if (game->map[next_y - 1][next_x] != WALL && steps < 2)
					{
						next_y--;
						moved = 1;
						steps++;
					}
					else
					{
						steps = 0;
						// Cambiar dirección horizontal
						game->enemies[i].direction = game->map[next_y][next_x + 1] != WALL ? 0 : 1;
					}
				}
				// Bajar
				else
				{
					if (game->map[next_y + 1][next_x] != WALL && steps < 2)
					{
						next_y++;
						moved = 1;
						steps++;
					}
					else
					{
						steps = 0;
						// Cambiar dirección horizontal
						game->enemies[i].direction = game->map[next_y][next_x + 1] != WALL ? 0 : 1;
					}
				}
			}
		}
		// Enemigo tipo N: mantener el movimiento vertical original
		else
		{
			// Movimiento vertical simple
			if (game->enemies[i].direction == 0)  // Abajo
			{
				if (game->map[next_y + 1][next_x] != WALL)
				{
					next_y++;
					moved = 1;
				}
				else
				{
					game->enemies[i].direction = 1;
					// Intentar moverse inmediatamente en la otra dirección
					if (game->map[next_y - 1][next_x] != WALL)
					{
						next_y--;
						moved = 1;
					}
				}
			}
			else  // Arriba
			{
				if (game->map[next_y - 1][next_x] != WALL)
				{
					next_y--;
					moved = 1;
				}
				else
				{
					game->enemies[i].direction = 0;
					// Intentar moverse inmediatamente en la otra dirección
					if (game->map[next_y + 1][next_x] != WALL)
					{
						next_y++;
						moved = 1;
					}
				}
			}
		}

		// Verificar si la nueva posición es válida
		if (moved)
		{
			// Comprobar colisión con jugador inmediatamente después del movimiento
			if (next_x == game->player.x && next_y == game->player.y)
			{
				game->state = STATE_LOSE;
				render_game(game);  // Renderizar inmediatamente para mostrar mensaje
				mlx_do_sync(game->mlx);  // Sincronizar para asegurar que se muestra
				usleep(1000000);  // Esperar 1 segundo
				close_window(game);
				return (1);
			}

			// Si hay colisión con otro enemigo
			if (check_enemy_collision(game, i, next_x, next_y))
			{
				// Para enemigos tipo X (horizontales)
				if (game->enemies[i].type == 1)
				{
					// Cambiar dirección
					game->enemies[i].direction = !game->enemies[i].direction;
					// Intentar moverse en la dirección opuesta
					next_x = game->enemies[i].pos.x;
					if (game->enemies[i].direction == 0 && game->map[next_y][next_x + 1] != WALL)
						next_x++;
					else if (game->enemies[i].direction == 1 && game->map[next_y][next_x - 1] != WALL)
						next_x--;
					
					// Verificar si la nueva posición está libre
					if (!check_enemy_collision(game, i, next_x, next_y))
					{
						game->enemies[i].pos.x = next_x;
						game->enemies[i].pos.y = next_y;
					}
				}
				// Para enemigos tipo N (verticales)
				else
				{
					// Cambiar dirección
					game->enemies[i].direction = !game->enemies[i].direction;
					// Intentar moverse en la dirección opuesta
					next_y = game->enemies[i].pos.y;
					if (game->enemies[i].direction == 0 && game->map[next_y + 1][next_x] != WALL)
						next_y++;
					else if (game->enemies[i].direction == 1 && game->map[next_y - 1][next_x] != WALL)
						next_y--;
					
					// Verificar si la nueva posición está libre
					if (!check_enemy_collision(game, i, next_x, next_y))
					{
						game->enemies[i].pos.x = next_x;
						game->enemies[i].pos.y = next_y;
					}
				}
			}
			else
			{
				// Si no hay colisión, mover normalmente
				game->enemies[i].pos.x = next_x;
				game->enemies[i].pos.y = next_y;

				// Comprobar colisión con jugador después del movimiento
				if (game->enemies[i].pos.x == game->player.x && 
					game->enemies[i].pos.y == game->player.y)
				{
					game->state = STATE_LOSE;
					render_game(game);  // Renderizar inmediatamente para mostrar mensaje
					mlx_do_sync(game->mlx);  // Sincronizar para asegurar que se muestra
					usleep(1000000);  // Esperar 1 segundo
					close_window(game);
					return (1);
				}
			}
		}
	}
	return (0);
}

// Función auxiliar para verificar colisiones entre enemigos
static int check_enemy_collision(t_game *game, int current_enemy, int x, int y)
{
	for (int i = 0; i < game->num_enemies; i++)
	{
		if (i != current_enemy && game->enemies[i].active &&
			game->enemies[i].pos.x == x && game->enemies[i].pos.y == y)
		{
			return 1;
		}
	}
	return 0;
}
