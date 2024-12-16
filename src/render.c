/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <string.h>

void	put_image_to_buffer(int *buffer, void *img, int x, int y, int buffer_width, float scale)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*img_data;
	int		scaled_size;
	
	img_data = (int *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
	scaled_size = TILE_SIZE * scale;
	
	for (int i = 0; i < scaled_size; i++)
	{
		for (int j = 0; j < scaled_size; j++)
		{
			int src_x = j / scale;
			int src_y = i / scale;
			int color = img_data[src_y * TILE_SIZE + src_x];
			if (color != 0)  // Solo copiar píxeles no transparentes
				buffer[(y + i) * buffer_width + (x + j)] = color;
		}
	}
}

void	*scale_image(t_game *game, void *original, float scale)
{
	int		width;
	int		height;
	void	*new_img;
	int		*orig_data;
	int		*new_data;
	int		bpp;
	int		size_line;
	int		endian;
	
	width = TILE_SIZE * scale;
	height = TILE_SIZE * scale;
	
	new_img = mlx_new_image(game->mlx, width, height);
	if (!new_img)
		return (NULL);
	
	orig_data = (int *)mlx_get_data_addr(original, &bpp, &size_line, &endian);
	new_data = (int *)mlx_get_data_addr(new_img, &bpp, &size_line, &endian);
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int orig_x = x / scale;
			int orig_y = y / scale;
			new_data[y * width + x] = orig_data[orig_y * TILE_SIZE + orig_x];
		}
	}
	
	return (new_img);
}

void	render_tile(t_game *game, int x, int y)
{
	void	*img_to_render;
	int		pos_x;
	int		pos_y;
	
	// Calcular posición con offset para centrado
	pos_x = ((game->window_width - (game->map_width * TILE_SIZE * game->scale_x)) / 2) + 
		(x * TILE_SIZE * game->scale_x);
	pos_y = ((game->window_height - (game->map_height * TILE_SIZE * game->scale_y)) / 2) + 
		(y * TILE_SIZE * game->scale_y);
	
	switch (game->map[y][x])
	{
		case WALL:
			img_to_render = game->img_wall;
			break;
		case PLAYER:
			img_to_render = game->img_player;
			break;
		case COLLECT:
			img_to_render = game->img_collect;
			break;
		case EXIT:
			img_to_render = game->img_exit;
			break;
		default:
			img_to_render = game->img_floor;
	}
	
	if (img_to_render)
		mlx_put_image_to_window(game->mlx, game->win, img_to_render, pos_x, pos_y);
}

int	render_game(t_game *game)
{
	int	x;
	int	y;
	
	ft_putendl_fd("\n=== Iniciando render_game ===\n", 1);
	if (!game || !game->mlx || !game->win || !game->map)
	{
		ft_putendl_fd("Error: Punteros nulos en render_game", 2);
		return (0);
	}
	
	// Limpiar la ventana
	mlx_clear_window(game->mlx, game->win);
	
	// Renderizar el mapa
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
	
	// Renderizar HUD
	render_hud(game);
	
	return (1);
}

void	render_hud(t_game *game)
{
	char moves_str[50];
	char collect_str[50];
	int text_size = 20 * game->scale_x;
	int margin = 10 * game->scale_x;
	
	if (!game || !game->mlx || !game->win)
	{
		ft_putendl_fd("Error: Punteros nulos en render_hud", 2);
		return;
	}
	
	snprintf(moves_str, sizeof(moves_str), "Moves: %d", game->moves);
	mlx_string_put(game->mlx, game->win, margin, text_size, 0xFFFFFF, moves_str);
	
	snprintf(collect_str, sizeof(collect_str), "Collected: %d/%d",
		game->collected, game->collectibles);
	mlx_string_put(game->mlx, game->win, margin, text_size * 2, 0xFFFFFF, collect_str);
}
