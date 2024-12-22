/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/so_long.h"

int	load_player_textures(t_game *game)
{
	const char	*texture_path;

	texture_path = find_texture_path("player/player.xpm");
	if (!texture_path)
		return (0);
	game->player.img = mlx_xpm_file_to_image(game->mlx,
			(char *)texture_path,
			&game->player.width,
			&game->player.height);
	if (!game->player.img)
		return (0);
	game->player.addr = mlx_get_data_addr(game->player.img,
			&game->player.bits_per_pixel,
			&game->player.line_length,
			&game->player.endian);
	if (!game->player.addr)
		return (0);
	return (1);
}
