/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size_chars_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P'
		|| c == 'N' || c == 'M' || c == 'n' || c == 'm');
}

static int	check_map_size(t_game *game)
{
	if (game->map_height > MAX_MAP_HEIGHT || game->map_width > MAX_MAP_WIDTH)
	{
		ft_putstr_fd("Error: Mapa demasiado grande\n", 1);
		return (0);
	}
	if (game->map_width < 3 || game->map_height < 3)
	{
		ft_putstr_fd("Error: Mapa demasiado pequeño\n", 1);
		return (0);
	}
	return (1);
}

static int	check_map_chars(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if (!check_map_char(game->map[i][j]))
			{
				ft_putstr_fd("Error: Carácter inválido en el mapa: ", 1);
				ft_putchar_fd(game->map[i][j], 1);
				ft_putstr_fd("\n", 1);
				return (0);
			}
		}
	}
	return (1);
}

int	check_map_size_and_chars(t_game *game)
{
	if (!check_map_size(game))
		return (0);
	if (!check_map_chars(game))
		return (0);
	return (1);
}
