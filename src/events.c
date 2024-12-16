#include "../inc/game.h"
#include "../libft/libft.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == WALL)
		return ;
	if (game->map[new_y][new_x] == COLLECT)
	{
		game->collected++;
		game->map[new_y][new_x] = EMPTY;
	}
	if (game->map[new_y][new_x] == EXIT && game->collected == game->collectibles)
	{
		ft_putstr_fd("\n¡Has ganado en ", 1);
		ft_putnbr_fd(game->moves + 1, 1);
		ft_putendl_fd(" movimientos!", 1);
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
		free_game(game);
		exit(0);
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
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_player(game, game->player.x, game->player.y - 1);
	else if (keycode == KEY_S)
		move_player(game, game->player.x, game->player.y + 1);
	else if (keycode == KEY_A)
		move_player(game, game->player.x - 1, game->player.y);
	else if (keycode == KEY_D)
		move_player(game, game->player.x + 1, game->player.y);
	return (0);
}

int	close_window(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = NULL;
	free_game(game);
	exit(0);
	return (0);
}
