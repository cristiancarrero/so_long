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
			if (color != (int)0x0)  // Solo copiar píxeles no transparentes
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
	int		pos_x;
	int		pos_y;
	int		bpp;
	int		size_line;
	int		endian;
	int		*floor_data;
	int		*obj_data;
	void	*img_to_render;
	
	pos_x = x * TILE_SIZE;
	pos_y = y * TILE_SIZE;
	
	// Inicializar img_to_render como NULL
	img_to_render = NULL;
	
	// Obtener datos del suelo
	floor_data = (int *)mlx_get_data_addr(game->img_floor, &bpp, &size_line, &endian);
	
	// Crear una imagen temporal para el resultado combinado
	void *combined = mlx_new_image(game->mlx, TILE_SIZE, TILE_SIZE);
	int *combined_data = (int *)mlx_get_data_addr(combined, &bpp, &size_line, &endian);
	
	// Copiar el suelo primero
	for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++)
		combined_data[i] = floor_data[i];
	
	// Obtener la imagen del objeto y combinarla
	if (game->map[y][x] == WALL)
		img_to_render = game->img_wall;
	else if (game->map[y][x] == PLAYER)
		img_to_render = game->img_player;
	else if (game->map[y][x] == COLLECT)
		img_to_render = game->img_collect;
	else if (game->map[y][x] == EXIT)
		img_to_render = game->img_exit;
	
	if (img_to_render != NULL)
	{
		obj_data = (int *)mlx_get_data_addr(img_to_render, &bpp, &size_line, &endian);
		for (int i = 0; i < TILE_SIZE * TILE_SIZE; i++)
		{
			unsigned int color = (unsigned int)obj_data[i];
			if (color != (unsigned int)0xFF000000 && color != 0)
				combined_data[i] = obj_data[i];
		}
	}
	
	// Renderizar la imagen combinada
	mlx_put_image_to_window(game->mlx, game->win, combined, pos_x, pos_y);
	mlx_destroy_image(game->mlx, combined);
}

void *create_buffer(t_game *game)
{
	void *buffer;
	int width = game->window_width;
	int height = game->window_height;

	buffer = mlx_new_image(game->mlx, width, height);
	return buffer;
}

int	render_game(t_game *game)
{
	int	x;
	int	y;
	
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
	int bar_width = 200;
	int bar_height = 20;
	int progress;
	
	if (!game || !game->mlx || !game->win)
	{
		ft_putendl_fd("Error: Punteros nulos en render_hud", 2);
		return;
	}
	
	snprintf(moves_str, sizeof(moves_str), "Moves: %d", game->moves);
	snprintf(collect_str, sizeof(collect_str), "Collected: %d/%d", 
			game->collected, game->collectibles);
	
	progress = (game->collected * bar_width) / game->collectibles;
	
	for (int i = 0; i < bar_width + 20; i++)
		for (int j = 0; j < bar_height + 40; j++)
			mlx_pixel_put(game->mlx, game->win, i + 10, j + 10, 0x000000);
	
	mlx_string_put(game->mlx, game->win, 20, 20, 0xFFFFFF, moves_str);
	mlx_string_put(game->mlx, game->win, 20, 40, 0xFFFFFF, collect_str);
	
	for (int i = 0; i < bar_width; i++)
	{
		int color = i < progress ? 0x00FF00 : 0x444444;
		mlx_pixel_put(game->mlx, game->win, i + 20, 60, color);
	}
}
