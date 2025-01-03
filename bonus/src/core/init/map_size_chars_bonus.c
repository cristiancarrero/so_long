/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size_chars_bonus.c                             :+:      :+:    :+:   */
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
				ft_putstr_fd("Error: Caracter inválido en el mapa\n", 2);
				return (0);
			}
		}
	}
	return (1);
}
