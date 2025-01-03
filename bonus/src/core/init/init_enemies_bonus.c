/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

static void	set_enemy_type(t_enemy *enemy, char type)
{
	if (type == 'N')
		enemy->type = 0;
	else
		enemy->type = 1;
}

void	init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	enemy_count;

	enemy_count = 0;
	i = 0;
	while (i < game->map_height && enemy_count < MAX_ENEMIES)
	{
		j = 0;
		while (j < game->map_width && enemy_count < MAX_ENEMIES)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'M')
			{
				game->enemies[enemy_count].x = j;
				game->enemies[enemy_count].y = i;
				game->enemies[enemy_count].direction = 1;
				game->enemies[enemy_count].frame = 0;
				set_enemy_type(&game->enemies[enemy_count], game->map[i][j]);
				enemy_count++;
			}
			j++;
		}
		i++;
	}
	game->num_enemies = enemy_count;
}
