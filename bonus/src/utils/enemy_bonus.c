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

static void	init_enemy_vars(t_game *game, int x, int y, int *count)
{
	game->enemies[*count].x = x;
	game->enemies[*count].y = y;
	game->enemies[*count].direction = 0;
	game->enemies[*count].frame = 0;
	if (game->map[y][x] == 'M')
		game->enemies[*count].type = 1;
	else
		game->enemies[*count].type = 0;
	(*count)++;
}

static void	process_enemy_init(t_game *game, int *count)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height && *count < game->num_enemies)
	{
		x = 0;
		while (x < game->map_width && *count < game->num_enemies)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'M')
				init_enemy_vars(game, x, y, count);
			x++;
		}
		y++;
	}
}

void	init_enemies(t_game *game)
{
	int	count;

	if (game->num_enemies == 0)
	{
		ft_putstr_fd("No hay enemigos para inicializar\n", 1);
		return ;
	}
	if (game->num_enemies > MAX_ENEMIES)
	{
		ft_putstr_fd("Advertencia: Limitando a ", 1);
		ft_putnbr_fd(MAX_ENEMIES, 1);
		ft_putstr_fd("\n", 1);
		game->num_enemies = MAX_ENEMIES;
	}
	count = 0;
	process_enemy_init(game, &count);
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
			ft_putstr_fd("¡Has chocado con un enemigo!\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}
