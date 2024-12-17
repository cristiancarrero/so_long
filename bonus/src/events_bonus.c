#include "../inc/game_bonus.h"
#include "../libft/libft.h"

void setup_hooks(t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return;

	// Configurar los hooks básicos
	mlx_hook(game->win, X_EVENT_KEY_PRESS, KeyPressMask, key_press, game);
	mlx_hook(game->win, X_EVENT_EXIT, NoEventMask, close_window, game);

	// Desactivar autorepetición de teclas
	mlx_do_key_autorepeatoff(game->mlx);

	// Añadir otros hooks específicos del bonus si los hay
}

static int load_next_level(t_game *game)
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

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == WALL)
		return ;

	// Comprobar colisión con enemigos
	for (int i = 0; i < game->num_enemies; i++)
	{
		if (new_x == game->enemies[i].pos.x && new_y == game->enemies[i].pos.y)
		{
			ft_putendl_fd("\n¡Has muerto! Fin del juego.", 1);
			close_window(game);
			return;
		}
	}

	if (game->map[new_y][new_x] == COLLECT)
	{
		game->collected++;
		game->map[new_y][new_x] = EMPTY;
	}
	if (game->map[new_y][new_x] == EXIT)
	{
		if (game->collected == game->collectibles)
		{
			ft_putstr_fd("Coleccionables recogidos: ", 1);
			ft_putnbr_fd(game->collected, 1);
			ft_putstr_fd("/", 1);
			ft_putnbr_fd(game->collectibles, 1);
			ft_putchar_fd('\n', 1);

			game->map[game->player.y][game->player.x] = EMPTY;
			game->map[new_y][new_x] = PLAYER;
			game->player.x = new_x;
			
			game->moves++;

			render_game(game);

			ft_putstr_fd("\n¡Nivel ", 1);
			ft_putnbr_fd(game->current_level, 1);
			ft_putstr_fd(" completado en ", 1);
			ft_putnbr_fd(game->moves, 1);
			ft_putendl_fd(" movimientos!", 1);

			if (ft_strnstr(game->level_paths[game->current_level - 1], "map3.ber", ft_strlen(game->level_paths[game->current_level - 1])))
			{
				ft_putendl_fd("\n¡Felicidades! ¡Has completado todos los niveles!", 1);
				close_window(game);
				return;
			}

			if (!load_next_level(game))
			{
				close_window(game);
				return;
			}
			return;
		}
		return ; // Si no has recogido todas las monedas, no puedes moverte a la salida
	}
	game->map[game->player.y][game->player.x] = EMPTY;
	game->map[new_y][new_x] = PLAYER;
	game->player.x = new_x;
	game->player.y = new_y;
	game->moves++;
	ft_putstr_fd("Movimientos: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putchar_fd('\n', 1);
	render_game(game);
}

int	key_press(int keycode, t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return (0);

	if (keycode == KEY_ESC || keycode == KEY_Q)
		close_window(game);
	else if (game->state == STATE_PLAYING)
	{
		if (keycode == KEY_W)
			move_player(game, game->player.x, game->player.y - 1);
		else if (keycode == KEY_S)
			move_player(game, game->player.x, game->player.y + 1);
		else if (keycode == KEY_A)
			move_player(game, game->player.x - 1, game->player.y);
		else if (keycode == KEY_D)
			move_player(game, game->player.x + 1, game->player.y);
	}

	return (0);
}

int	close_window(t_game *game)
{
	ft_putendl_fd("\n=== Iniciando close_window ===", 1);
	if (!game)
	{
		ft_putendl_fd("Error: game es NULL en close_window", 2);
		_exit(1);
	}
	ft_putstr_fd("Dirección de game: 0x", 1);
	ft_putstr_fd("ADDR", 1);  // O simplemente indicar que es un puntero
	ft_putchar_fd('\n', 1);

	game->state = STATE_LOSE;
	ft_putendl_fd("Estado cambiado a STATE_LOSE", 1);

	if (game->win)
	{
		// Destruir el back buffer si existe
		if (game->back_buffer)
		{
			mlx_destroy_image(game->mlx, game->back_buffer);
			game->back_buffer = NULL;
		}

		// Destruir todas las imágenes
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

		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->win = NULL;
		game->mlx = NULL;
		game->img_wall = NULL;
		game->img_floor = NULL;
		game->img_player = NULL;
		game->img_collect = NULL;
		game->img_exit = NULL;
	}

	free_game(game);
	_exit(0);
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

void    move_enemies(t_game *game)
{
	if (!game || !game->enemies || game->num_enemies <= 0)
		return;
	
	static int delay = 0;
	delay++;
	if (delay < 8)
		return;
	delay = 0;
	
	for (int i = 0; i < game->num_enemies; i++)
	{
		// Movimiento horizontal o vertical
		static int move_pattern = 0;
		move_pattern = (move_pattern + 1) % 2;

		int old_x = game->enemies[i].pos.x;
		int old_y = game->enemies[i].pos.y;

		if (move_pattern == 0)
			game->enemies[i].pos.x += game->enemies[i].direction;
		else
			game->enemies[i].pos.y += game->enemies[i].direction;

		// Verificar colisiones y límites
		if (game->enemies[i].pos.x >= game->enemies[i].patrol_end ||
			game->enemies[i].pos.x <= game->enemies[i].patrol_start ||
				game->map[game->enemies[i].pos.y][game->enemies[i].pos.x] == WALL ||
				game->enemies[i].pos.y < 1 ||
				game->enemies[i].pos.y >= game->map_height - 1)
		{
			game->enemies[i].direction *= -1;
			game->enemies[i].pos.x = old_x;
			game->enemies[i].pos.y = old_y;
		}
		
		if (game->enemies[i].pos.x == game->player.x &&
			game->enemies[i].pos.y == game->player.y)
		{
			ft_putendl_fd("\n¡Has muerto! Fin del juego.", 1);
			close_window(game);
			return;
		}
	}
}
