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

#include "so_long_bonus.h"

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

int	check_map_size_and_chars(t_game *game)
{
	int	i;
	int	j;

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
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] != '0' && game->map[i][j] != '1' &&
				game->map[i][j] != 'C' && game->map[i][j] != 'E' &&
				game->map[i][j] != 'P' && game->map[i][j] != 'N' &&
				game->map[i][j] != 'M' && game->map[i][j] != 'n' &&
				game->map[i][j] != 'm')
			{
				ft_putstr_fd("Error: Carácter inválido en el mapa: ", 1);
				ft_putchar_fd(game->map[i][j], 1);
				ft_putstr_fd("\n", 1);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
