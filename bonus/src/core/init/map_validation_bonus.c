/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	count_map_elements(t_game *game, int *player, int *exit)
{
	t_count_params	p;

	p.player = player;
	p.exit = exit;
	p.i = 0;
	while (p.i < game->map_height)
	{
		p.j = 0;
		while (p.j < game->map_width)
		{
			if (game->map[p.i][p.j] == 'P')
			{
				(*p.player)++;
				game->player_x = p.j;
				game->player_y = p.i;
			}
			else if (game->map[p.i][p.j] == 'E')
				(*p.exit)++;
			else if (game->map[p.i][p.j] == 'C')
				game->collectibles++;
			p.j++;
		}
		p.i++;
	}
}

int	check_characters(t_game *game)
{
	int	player;
	int	exit;

	player = 0;
	exit = 0;
	game->collectibles = 0;
	count_map_elements(game, &player, &exit);
	if (player != 1)
	{
		ft_putstr_fd("Error: Debe haber exactamente un jugador\n", 1);
		return (0);
	}
	if (exit != 1)
	{
		ft_putstr_fd("Error: Debe haber exactamente una salida\n", 1);
		return (0);
	}
	if (game->collectibles < 1)
	{
		ft_putstr_fd("Error: Debe haber al menos un coleccionable\n", 1);
		return (0);
	}
	return (1);
}
