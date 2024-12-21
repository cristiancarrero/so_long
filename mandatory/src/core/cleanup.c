#include "../../inc/game.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
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
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->back_buffer)
			mlx_destroy_image(game->mlx, game->back_buffer);
		if (game->player.sprite_left && game->player.sprite_left != game->img_player)
			mlx_destroy_image(game->mlx, game->player.sprite_left);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
		free_map(game->map);
}

void	cleanup_game(t_game *game)
{
	free_game(game);
	exit(0);
} 