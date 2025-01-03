/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

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
				ft_putstr_fd("Error: Caracter inválido en el mapa\n", 2);
				return (0);
			}
		}
	}
	return (1);
}

int	check_rectangular(t_game *game)
{
	int		i;
	size_t	expected_len;

	if (game->map_height < 1)
		return (0);
	expected_len = ft_strlen(game->map[0]);
	game->map_width = (int)expected_len;
	i = 1;
	while (i < game->map_height)
	{
		if (ft_strlen(game->map[i]) != expected_len)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (++j < game->map_width)
		{
			if ((i == 0 || i == game->map_height - 1
					|| j == 0 || j == game->map_width - 1)
				&& game->map[i][j] != '1')
				return (0);
		}
	}
	return (1);
}
