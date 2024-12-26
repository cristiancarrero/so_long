/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	put_pixel_to_hud(t_img *buffer, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < buffer->width && y < buffer->height)
	{
		dst = buffer->addr + (y * buffer->line_length + x
				* (buffer->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static unsigned int	get_button_color(int i, int j, int width, int height)
{
	if (i < 0 || i >= width || j < 0 || j >= height)
		return (0xFF8B4513);
	if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
		return (0xFF9B5523);
	if (j < height / 2)
		return (0xFFE6C89C);
	return (0xFFD4A76A);
}

void	render_button_background(t_game *game, int x, int y, int width)
{
	int				height;
	int				i;
	int				j;
	int				border;

	height = 25;
	border = 2;
	i = -border;
	while (i < width + border)
	{
		j = -border;
		while (j < height + border)
		{
			put_pixel_to_hud(&game->buffer, x + i, y + j,
				get_button_color(i, j, width, height));
			j++;
		}
		i++;
	}
}
