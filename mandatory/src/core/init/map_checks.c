/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

int	check_rectangular(t_game *game)
{
	int	i;
	int	len;

	len = ft_strlen(game->map[0]);
	i = 0;
	while (i < game->map_height)
	{
		if ((int)ft_strlen(game->map[i]) != len)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_game *game)
{
	int				i;
	int				j;
	int				is_border;
	t_check_params	p;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			p.x = j;
			p.y = i;
			p.width = game->map_width;
			p.height = game->map_height;
			is_border = (p.y == 0 || p.y == p.height - 1
					|| p.x == 0 || p.x == p.width - 1);
			if (is_border && game->map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	update_counts(t_game *game, char c, t_count_params p)
{
	if (c == 'P' && ++(*p.player))
	{
		game->player_x = p.j;
		game->player_y = p.i;
	}
	else if (c == 'C')
		game->collectibles++;
	else if (c == 'E')
		++(*p.exit);
}

int	check_characters(t_game *game)
{
	int				i;
	int				j;
	int				player;
	int				exit;
	t_count_params	p;

	i = -1;
	player = 0;
	exit = 0;
	game->collectibles = 0;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (game->map[i][j] != '0' && game->map[i][j] != '1')
			{
				p = (t_count_params){&player, &exit, i, j};
				update_counts(game, game->map[i][j], p);
			}
		}
	}
	return (player == 1 && game->collectibles > 0 && exit == 1);
}
