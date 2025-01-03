/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
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

static int	validate_map_structure(t_game *game)
{
	if (!check_rectangular(game))
	{
		ft_putstr_fd("Error: El mapa no es rectangular\n", 2);
		return (0);
	}
	if (!check_walls(game))
	{
		ft_putstr_fd("Error: El mapa no está rodeado de muros\n", 2);
		return (0);
	}
	return (1);
}

static int	validate_map_content(t_game *game)
{
	if (!check_map_size_and_chars(game))
		return (0);
	if (!check_characters(game))
	{
		ft_putstr_fd("Error: Configuración de caracteres inválida\n", 2);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!validate_map_content(game))
		return (0);
	if (!validate_map_structure(game))
		return (0);
	if (!check_path(game))
	{
		ft_putstr_fd("Error: No hay un camino válido al objetivo\n", 2);
		return (0);
	}
	return (1);
}
