/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	put_pixel_to_sprite(t_img *buffer, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= buffer->width || y >= buffer->height)
		return ;
	dst = buffer->addr + (y * buffer->line_length + x * \
		(buffer->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static unsigned int	get_sprite_pixel(t_img *img, int i, int j)
{
	char	*src;

	if (i < 0 || j < 0 || i >= img->height || j >= img->width)
		return (0);
	src = img->addr + (i * img->line_length + j * (img->bits_per_pixel / 8));
	return (*(unsigned int *)src);
}

static void	put_pixel_with_flip(t_game *game, t_copy_params p, int i, int j)
{
	unsigned int	color;
	int				x;
	int				y;

	color = get_sprite_pixel(p.img, i, j);
	if (color != 0xFF000000)
	{
		if ((p.is_player && game->is_facing_left)
			|| (!p.is_player && p.direction == 0))
			x = p.x * TILE_SIZE + (TILE_SIZE - 1 - j);
		else
			x = p.x * TILE_SIZE + j;
		y = p.y * TILE_SIZE + i;
		if (x >= 0 && x < game->buffer.width && y >= 0
			&& y < game->buffer.height)
			put_pixel_to_sprite(&game->buffer, x, y, color);
	}
}

void	copy_image_to_buffer(t_game *game, t_copy_params params)
{
	int	i;
	int	j;

	if (!params.img || !params.img->img || !game->buffer.img)
		return ;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			put_pixel_with_flip(game, params, i, j);
			j++;
		}
		i++;
	}
}
