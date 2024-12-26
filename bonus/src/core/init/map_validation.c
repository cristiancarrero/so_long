/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

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

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

static int	check_size(t_game *game)
{
	if (game->map_width > MAX_MAP_WIDTH || game->map_height > MAX_MAP_HEIGHT)
	{
		ft_putstr_fd("Error: Mapa demasiado grande\n", 2);
		return (0);
	}
	if (game->map_width < 3 || game->map_height < 3)
	{
		ft_putstr_fd("Error: Mapa demasiado pequeño\n", 2);
		return (0);
	}
	return (1);
}

int	check_map_size_and_chars(t_game *game)
{
	int	i;
	int	j;

	if (!check_size(game))
		return (0);
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (!is_valid_char(game->map[i][j]))
			{
				ft_putstr_fd("Error: Caracter inválido en el mapa: ", 2);
				ft_putchar_fd(game->map[i][j], 2);
				ft_putchar_fd('\n', 2);
				return (0);
			}
		}
	}
	return (1);
}
