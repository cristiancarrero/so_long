/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_count_params(t_count_params *params)
{
	*params->player = 0;
	*params->exit = 0;
	params->i = 0;
	params->j = 0;
}

static int	check_valid_chars(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P'
		|| c == 'N' || c == 'M');
}

static int	update_counts(t_count_params *params, char c, t_game *game)
{
	if (!check_valid_chars(c))
		return (0);
	if (c == 'P')
	{
		(*params->player)++;
		game->player_x = params->j;
		game->player_y = params->i;
	}
	else if (c == 'E')
		(*params->exit)++;
	else if (c == 'C')
		game->collectibles++;
	return (1);
}

int	check_characters(t_game *game)
{
	t_count_params	params;
	int				player;
	int				exit;

	player = 0;
	exit = 0;
	game->collectibles = 0;
	params.player = &player;
	params.exit = &exit;
	init_count_params(&params);
	while (params.i < game->map_height)
	{
		params.j = 0;
		while (params.j < game->map_width)
		{
			if (!update_counts(&params, game->map[params.i][params.j], game))
				return (0);
			params.j++;
		}
		params.i++;
	}
	if (player != 1 || exit != 1 || game->collectibles < 1)
		return (0);
	return (1);
} 