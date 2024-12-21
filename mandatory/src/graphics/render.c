/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static void	put_pixel_to_buffer(t_img *buffer, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < buffer->width && y < buffer->height)
	{
		dst = buffer->addr + (y * buffer->line_length + x
				* (buffer->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	copy_image_to_buffer(t_game *game, t_img *img, int x, int y)
{
	unsigned int	color;
	int			i;
	int			j;

	if (!img || !img->img || !img->addr)
		return ;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			color = *(unsigned int *)(img->addr + (i * img->line_length
						+ j * (img->bits_per_pixel / 8)));
			if ((color & 0x00FFFFFF) != 0)
				put_pixel_to_buffer(&game->buffer,
					x * TILE_SIZE + j, y * TILE_SIZE + i, color);
			j++;
		}
		i++;
	}
}

static void	render_background(t_game *game)
{
	int	x;
	int	y;

	y = 1;
	while (y < game->map_height)
	{
		x = 1;
		while (x < game->map_width)
		{
			copy_image_to_buffer(game, &game->floor, x, y);
			x++;
		}
		y++;
	}
}

static void	render_tile(t_game *game, int x, int y)
{
	char	tile;

	tile = game->map[y][x];
	if (tile == '1')
		copy_image_to_buffer(game, &game->wall, x, y);
	else if (y > 0 && x > 0)
	{
		if (tile == 'P')
		{
			if (game->is_facing_left)
				copy_image_to_buffer(game, &game->player_left, x, y);
			else
				copy_image_to_buffer(game, &game->player, x, y);
		}
		else if (tile == 'C')
			copy_image_to_buffer(game, &game->collect, x, y);
		else if (tile == 'E')
			copy_image_to_buffer(game, &game->exit, x, y);
	}
}

static void	render_button_background(t_game *game, int x, int y, int width)
{
	int			height;
	int			i;
	int			j;
	int			border;
	unsigned int	color;

	height = 25;
	border = 3;
	i = -border;
	while (i < width + border)
	{
		j = -border;
		while (j < height + border)
		{
			if (i < 0 || i >= width || j < 0 || j >= height)
				color = 0xFF8B4513;
			else if (j < height / 2)
				color = 0xFFD2B48C;
			else
				color = 0xFFBC8F8F;
			put_pixel_to_buffer(&game->buffer, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	char	*moves_str;
	char	*collect_str;
	char	moves_msg[50];
	char	collect_msg[50];

	if (!game || !game->mlx || !game->win)
		return ;
	render_background(game);
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			render_tile(game, x, y);
	}
	render_button_background(game, 5, 5, 120);
	render_button_background(game, game->map_width * TILE_SIZE - 125, 5, 120);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.img, 0, 0);
	moves_str = ft_itoa(game->moves);
	collect_str = ft_itoa(game->collected);
	ft_strlcpy(moves_msg, "Moves: ", sizeof(moves_msg));
	ft_strlcat(moves_msg, moves_str, sizeof(moves_msg));
	ft_strlcpy(collect_msg, "Items: ", sizeof(collect_msg));
	ft_strlcat(collect_msg, collect_str, sizeof(collect_msg));
	ft_strlcat(collect_msg, "/", sizeof(collect_msg));
	free(collect_str);
	collect_str = ft_itoa(game->collectibles);
	ft_strlcat(collect_msg, collect_str, sizeof(collect_msg));
	mlx_string_put(game->mlx, game->win, 25, 20, 0xFF000000, moves_msg);
	mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE - 110,
		20, 0xFF000000, collect_msg);
	free(moves_str);
	free(collect_str);
}

int	render_frame(t_game *game)
{
	render_map(game);
	return (0);
}
