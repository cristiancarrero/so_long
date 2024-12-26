/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	load_textures(t_game *game)
{
	ft_putstr_fd("\n=== Iniciando carga de texturas ===\n", 1);
	
	ft_putstr_fd("Cargando texturas del jugador...\n", 1);
	if (!load_player_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas del jugador\n", 1);
		return (0);
	}
	
	ft_putstr_fd("Cargando texturas de coleccionables...\n", 1);
	if (!load_collect_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas de coleccionables\n", 1);
		return (0);
	}
	
	ft_putstr_fd("Cargando texturas de salida...\n", 1);
	if (!load_exit_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas de salida\n", 1);
		return (0);
	}
	
	ft_putstr_fd("Cargando texturas de paredes y suelo...\n", 1);
	if (!load_wall_floor_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas de paredes y suelo\n", 1);
		return (0);
	}
	
	ft_putstr_fd("=== Todas las texturas cargadas con éxito ===\n\n", 1);
	return (1);
}
