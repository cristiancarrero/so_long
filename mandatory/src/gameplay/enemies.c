#include "../../inc/game.h"

static int	can_move_enemy(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		return (0);
	if (game->map[y][x] == WALL || game->map[y][x] == EXIT ||
		game->map[y][x] == COLLECT)
		return (0);
	return (1);
}

static void	update_enemy_position(t_game *game, t_enemy *enemy,
	int new_x, int new_y)
{
	game->map[enemy->y][enemy->x] = EMPTY;
	enemy->x = new_x;
	enemy->y = new_y;
	game->map[enemy->y][enemy->x] = ENEMY;
}

void	init_enemies(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == ENEMY)
				count++;
			x++;
		}
		y++;
	}

	game->num_enemies = count;
	if (count > 0)
	{
		game->enemies = ft_calloc(count, sizeof(t_enemy));
		if (!game->enemies)
			return ;

		count = 0;
		y = 0;
		while (y < game->map_height)
		{
			x = 0;
			while (x < game->map_width)
			{
				if (game->map[y][x] == ENEMY)
				{
					game->enemies[count].x = x;
					game->enemies[count].y = y;
					game->enemies[count].active = 1;
					game->enemies[count].direction = 1;
					count++;
				}
				x++;
			}
			y++;
		}
	}
}

void	move_enemies(t_game *game)
{
	int		i;
	int		new_x;
	int		new_y;
	t_enemy	*enemy;

	i = 0;
	while (i < game->num_enemies)
	{
		enemy = &game->enemies[i];
		if (enemy->active)
		{
			new_x = enemy->x;
			new_y = enemy->y;

			if (enemy->direction == 1)
				new_x++;
			else
				new_x--;

			if (can_move_enemy(game, new_x, new_y))
				update_enemy_position(game, enemy, new_x, new_y);
			else
				enemy->direction *= -1;

			if (enemy->x == game->player.x && enemy->y == game->player.y)
			{
				ft_putendl_fd("\n¡Has perdido! Te ha atrapado un enemigo.", 1);
				game->state = STATE_LOSE;
				return ;
			}
		}
		i++;
	}
}

void	cleanup_enemies(t_game *game)
{
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
	game->num_enemies = 0;
} 