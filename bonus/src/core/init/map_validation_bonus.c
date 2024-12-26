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

int	validate_map(t_game *game)
{
	if (!check_rectangular(game))
	{
		ft_putstr_fd("Error: El mapa no es rectangular\n", 1);
		return (0);
	}
	if (!check_walls(game))
	{
		ft_putstr_fd("Error: El mapa no está rodeado por muros\n", 1);
		return (0);
	}
	if (!check_characters(game))
	{
		ft_putstr_fd("Error: Número incorrecto de jugadores o salidas\n", 1);
		return (0);
	}
	if (!check_map_size_and_chars(game))
		return (0);
	return (1);
}
