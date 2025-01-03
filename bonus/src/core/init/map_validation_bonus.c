/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

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
		ft_putstr_fd("Error: Debe haber un jugador (P), una salida (E)\n", 2);
		ft_putstr_fd("y al menos un coleccionable (C)\n", 2);
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!validate_map_structure(game))
		return (0);
	if (!validate_map_content(game))
		return (0);
	if (!check_path(game))
	{
		ft_putstr_fd("Error: No hay un camino válido al objetivo\n", 2);
		return (0);
	}
	return (1);
}
