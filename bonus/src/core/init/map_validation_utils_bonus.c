/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long_bonus.h"

int	validate_map_dimensions(t_game *game)
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

int	validate_map_content(t_game *game)
{
	if (!check_characters(game))
	{
		ft_putstr_fd("Error: Caracteres inválidos en el mapa\n", 2);
		return (0);
	}
	if (!check_path(game))
	{
		ft_putstr_fd("Error: No hay camino válido\n", 2);
		return (0);
	}
	return (1);
}
