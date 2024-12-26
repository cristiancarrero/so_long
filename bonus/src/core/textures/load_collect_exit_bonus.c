/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_collect_exit_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	load_collect_textures(t_game *game)
{
	const char	*collect_path;

	ft_putstr_fd("Intentando cargar textura de coleccionable...\n", 1);
	collect_path = "./textures/bonus/collect/collect.xpm";
	ft_putstr_fd("Ruta del coleccionable: ", 1);
	ft_putstr_fd((char *)collect_path, 1);
	ft_putstr_fd("\n", 1);
	game->collect.img = mlx_xpm_file_to_image(game->mlx,
			(char *)collect_path,
			&game->collect.width,
			&game->collect.height);
	if (!game->collect.img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen del coleccionable\n", 1);
		return (0);
	}
	game->collect.addr = mlx_get_data_addr(game->collect.img,
			&game->collect.bits_per_pixel,
			&game->collect.line_length,
			&game->collect.endian);
	if (!game->collect.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos del coleccionable\n", 1);
		return (0);
	}
	ft_putstr_fd("Textura del coleccionable cargada con éxito\n", 1);
	return (1);
}

int	load_exit_textures(t_game *game)
{
	const char	*exit_path;

	ft_putstr_fd("Intentando cargar textura de salida...\n", 1);
	exit_path = "./textures/bonus/door/exit.xpm";
	ft_putstr_fd("Ruta de la salida: ", 1);
	ft_putstr_fd((char *)exit_path, 1);
	ft_putstr_fd("\n", 1);
	game->exit.img = mlx_xpm_file_to_image(game->mlx,
			(char *)exit_path,
			&game->exit.width,
			&game->exit.height);
	if (!game->exit.img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen de la salida\n", 1);
		return (0);
	}
	game->exit.addr = mlx_get_data_addr(game->exit.img,
			&game->exit.bits_per_pixel,
			&game->exit.line_length,
			&game->exit.endian);
	if (!game->exit.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos de la salida\n", 1);
		return (0);
	}
	ft_putstr_fd("Textura de la salida cargada con éxito\n", 1);
	return (1);
}
