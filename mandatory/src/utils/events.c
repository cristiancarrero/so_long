#include "../../inc/game.h"

int	key_press(int keycode, t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return (0);

	if (keycode == KEY_ESC)
	{
		close_window(game);
		return (0);
	}

	if (game->state == STATE_PLAYING)
	{
		int new_x = game->player.x;
		int new_y = game->player.y;

		switch (keycode)
		{
			case KEY_W:
			case KEY_UP:
				new_y--;
				break;
			case KEY_S:
			case KEY_DOWN:
				new_y++;
				break;
			case KEY_A:
			case KEY_LEFT:
				new_x--;
				break;
			case KEY_D:
			case KEY_RIGHT:
				new_x++;
				break;
			default:
				return (0);
		}

		if (!check_collision(game, new_x, new_y))
			move_player(game, new_x, new_y);
	}
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_game(game);
	exit(0);
}

int	handle_resize(int width, int height, t_game *game)
{
	static int last_width = 0;
	static int last_height = 0;

	if (!game || !game->mlx || !game->win)
		return (0);

	// Calcular dimensiones mínimas basadas en el mapa
	int min_width = game->map_width * TILE_SIZE;
	int min_height = game->map_height * TILE_SIZE;

	// Asegurar tamaño mínimo
	if (width < min_width)
		width = min_width;
	if (height < min_height)
		height = min_height;

	// Evitar actualizaciones innecesarias
	if (width == last_width && height == last_height)
		return (0);

	// Actualizar dimensiones
	game->window_width = width;
	game->window_height = height;

	// Forzar un nuevo renderizado
	render_game(game);

	last_width = width;
	last_height = height;

	return (0);
}

void	setup_hooks(t_game *game)
{
	ft_putendl_fd("Configurando hooks...", 1);
	
	if (!game || !game->mlx || !game->win)
	{
		ft_putendl_fd("Error: Punteros nulos en setup_hooks", 2);
		return;
	}

	mlx_hook(game->win, X_EVENT_KEY_PRESS, KeyPressMask, key_press, game);
	mlx_hook(game->win, X_EVENT_EXIT, NoEventMask, close_window, game);
	mlx_hook(game->win, X_EVENT_RESIZE, StructureNotifyMask, handle_resize, game);
	mlx_do_key_autorepeaton(game->mlx);  // Activar auto-repeat para teclas
	mlx_expose_hook(game->win, render_game, game);
	mlx_loop_hook(game->mlx, render_game, game);
	
	ft_putendl_fd("Hooks configurados correctamente", 1);
}
