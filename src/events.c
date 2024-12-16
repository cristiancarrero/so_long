#include "../inc/game.h"
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
}

int	close_window(t_game *game)
{
	if (!game)
	{
		ft_putendl_fd("Error: game es NULL en close_window", 2);
		_exit(1);
	}

	game->state = STATE_LOSE;

	if (game->win)
	{
		if (game->back_buffer)
		{
			mlx_destroy_image(game->mlx, game->back_buffer);
			game->back_buffer = NULL;
		}

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

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == WALL)
		return;

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

			ft_putendl_fd("\n¡Has ganado!", 1);
			close_window(game);
			return;
		}
		return;
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
