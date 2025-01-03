/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P'
		|| c == 'N' || c == 'M');
}

static int	process_char(t_game *game, char c, t_counts *counts, t_pos pos)
{
	if (!is_valid_char(c))
	{
		print_char_error(c);
		return (0);
	}
	if (c == 'P' && ++counts->player)
	{
		game->player_x = pos.x;
		game->player_y = pos.y;
	}
	else if (c == 'C')
		game->collectibles++;
	else if (c == 'E')
		++counts->exit;
	else if (c == 'N' || c == 'M')
		game->num_enemies++;
	return (1);
}

int	check_characters(t_game *game)
{
	t_counts	counts;
	t_pos		pos;

	init_counts(game, &counts);
	pos.y = -1;
	while (++pos.y < game->map_height)
	{
		pos.x = -1;
		while (++pos.x < game->map_width)
			if (!process_char(game, game->map[pos.y][pos.x], &counts, pos))
				return (0);
	}
	if (counts.player != 1 || counts.exit != 1 || game->collectibles < 1)
	{
		if (counts.player != 1)
			print_config_error(0);
		else if (counts.exit != 1)
			print_config_error(1);
		else
			print_config_error(2);
		return (0);
	}
	return (1);
}
