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

static int	init_collect_texture(t_game *game)
{
	char	*path;

	init_img(&game->collect);
	path = (char *)find_texture_path("collect");
	if (!path)
	{
		ft_putstr_fd("Error\nNo se encontró la textura del coleccionable\n", 2);
		return (0);
	}
	game->collect.img = mlx_xpm_file_to_image(game->mlx, path,
			&game->collect.width, &game->collect.height);
	if (!game->collect.img)
	{
		ft_putstr_fd("Error\nNo se pudo cargar la textura: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	game->collect.addr = mlx_get_data_addr(game->collect.img,
			&game->collect.bits_per_pixel,
			&game->collect.line_length,
			&game->collect.endian);
	return (1);
}

static int	init_exit_texture(t_game *game)
{
	char	*path;

	init_img(&game->exit);
	path = (char *)find_texture_path("exit");
	if (!path)
	{
		ft_putstr_fd("Error\nNo se encontró la textura de la salida\n", 2);
		return (0);
	}
	game->exit.img = mlx_xpm_file_to_image(game->mlx, path,
			&game->exit.width, &game->exit.height);
	if (!game->exit.img)
	{
		ft_putstr_fd("Error\nNo se pudo cargar la textura: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	game->exit.addr = mlx_get_data_addr(game->exit.img,
			&game->exit.bits_per_pixel,
			&game->exit.line_length,
			&game->exit.endian);
	return (1);
}

int	load_collect_exit_textures(t_game *game)
{
	if (!init_collect_texture(game))
	{
		return (0);
	}
	if (!init_exit_texture(game))
	{
		if (game->collect.img)
			mlx_destroy_image(game->mlx, game->collect.img);
		return (0);
	}
	return (1);
}
