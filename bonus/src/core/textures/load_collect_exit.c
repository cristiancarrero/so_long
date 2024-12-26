/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_collect_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

int	load_collect_textures(t_game *game)
{
	const char	*texture_path;

	texture_path = find_texture_path("collect/collect.xpm");
	if (!texture_path)
		return (0);
	game->collect.img = mlx_xpm_file_to_image(game->mlx,
			(char *)texture_path,
			&game->collect.width,
			&game->collect.height);
	if (!game->collect.img)
		return (0);
	game->collect.addr = mlx_get_data_addr(game->collect.img,
			&game->collect.bits_per_pixel,
			&game->collect.line_length,
			&game->collect.endian);
	if (!game->collect.addr)
		return (0);
	return (1);
}

int	load_exit_textures(t_game *game)
{
	const char	*texture_path;

	texture_path = find_texture_path("door/exit.xpm");
	if (!texture_path)
		return (0);
	game->exit.img = mlx_xpm_file_to_image(game->mlx,
			(char *)texture_path,
			&game->exit.width,
			&game->exit.height);
	if (!game->exit.img)
		return (0);
	game->exit.addr = mlx_get_data_addr(game->exit.img,
			&game->exit.bits_per_pixel,
			&game->exit.line_length,
			&game->exit.endian);
	if (!game->exit.addr)
		return (0);
	return (1);
}
