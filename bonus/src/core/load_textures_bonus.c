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
	if (!load_wall_floor_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas de pared y suelo\n", 2);
		return (0);
	}
	if (!load_player_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas del jugador\n", 2);
		cleanup_images(game);
		return (0);
	}
	if (!load_collect_exit_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas de coleccionables y salida\n", 2);
		cleanup_images(game);
		return (0);
	}
	if (!load_enemy_textures(game))
	{
		ft_putstr_fd("Error al cargar texturas de enemigos\n", 2);
		cleanup_images(game);
		return (0);
	}
	return (1);
}
