/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	destroy_image(void *mlx, t_img *img)
{
	if (mlx && img && img->img)
	{
		mlx_destroy_image(mlx, img->img);
		img->img = NULL;
		img->addr = NULL;
	}
}

unsigned int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*pixel;

	if (!img || !img->addr || x < 0 || y < 0 || x >= TILE_SIZE
		|| y >= TILE_SIZE)
		return (0);
	pixel = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	put_pixel_to_buffer(t_img *buffer, int x, int y, unsigned int color)
{
	char	*dst;

	if (!buffer || !buffer->addr || x < 0 || y < 0
		|| x >= buffer->width || y >= buffer->height)
		return ;
	dst = buffer->addr + (y * buffer->line_length
			+ x * (buffer->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
