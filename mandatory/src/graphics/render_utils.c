/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static void	put_pixel_to_buffer(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < buffer->width && y < buffer->height)
	{
		dst = buffer->addr + (y * buffer->line_length + x
				* (buffer->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static unsigned int	get_pixel_color(t_img *img, int i, int j)
{
	return (*(unsigned int *)(img->addr + (i * img->line_length
			+ j * (img->bits_per_pixel / 8))));
}

static void	put_pixel_with_flip(t_game *game, t_copy_params p, int i, int j)
{
	unsigned int	color;
	int				x;
	int				y;

	color = get_pixel_color(p.img, i, j);
	if ((color & 0x00FFFFFF) != 0)
	{
		if (p.is_player && game->is_facing_left)
			x = p.x * TILE_SIZE + (TILE_SIZE - 1 - j);
		else
			x = p.x * TILE_SIZE + j;
		y = p.y * TILE_SIZE + i;
		put_pixel_to_buffer(&game->buffer, x, y, color);
	}
}

void	copy_image_to_buffer(t_game *game, t_copy_params params)
{
	int	i;
	int	j;

	if (!params.img || !params.img->img || !params.img->addr || params.x < 0
		|| params.y < 0 || params.x >= game->map_width
		|| params.y >= game->map_height)
		return ;
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			put_pixel_with_flip(game, params, i, j);
	}
}
