/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game_bonus.h"

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
			unsigned int color = (unsigned int)img_data[src_y * TILE_SIZE + src_x];
			if (color != 0 && color != (unsigned int)0xFF000000 && (color & 0x00FFFFFF) != 0)
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

void	render_enemies(t_game *game)
{
	int pos_x, pos_y;
	int *buffer_data;
	int bpp, size_line, endian;

	if (!game->enemies || game->num_enemies <= 0)
		return;

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp, &size_line, &endian);

	for (int i = 0; i < game->num_enemies; i++)
	{
		if (game->enemies[i].active && game->enemies[i].current)
		{
			pos_x = game->enemies[i].pos.x * TILE_SIZE * game->scale_x;
			pos_y = game->enemies[i].pos.y * TILE_SIZE * game->scale_y;

			// Dibujar el enemigo en el buffer
			put_image_to_buffer(
				buffer_data,
				game->enemies[i].current,
				pos_x,
				pos_y,
				game->window_width,
				game->scale_x
			);
		}
	}
}

int	render_game(t_game *game)
{
	int	x;
	int	y;
	int	pos_x;
	int	pos_y;
	void	*img_to_render;
	int		*buffer_data;
	int		bpp;
	int		size_line;
	int		endian;

	if (!game || !game->mlx || !game->win || !game->map)
		return (0);

	if (!game->img_floor || !game->img_wall || !game->img_player || 
		!game->img_collect || !game->img_exit)
		return (0);

	// Asegurarnos de que tenemos un buffer válido
	if (!game->back_buffer)
	{
		game->back_buffer = mlx_new_image(game->mlx, game->window_width, game->window_height);
		if (!game->back_buffer)
			return (0);
	}

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp, &size_line, &endian);
	if (!buffer_data)
		return (0);

	// Limpiar el buffer
	for (int i = 0; i < game->window_height; i++)
		ft_memset(buffer_data + (i * size_line / 4), 0, size_line);

	// Calcular escalas y offsets
	if (game->window_width > 0 && game->map_width > 0)
		game->scale_x = (float)game->window_width / (game->map_width * TILE_SIZE);
	else
		game->scale_x = 1.0;

	if (game->window_height > 0 && game->map_height > 0)
		game->scale_y = (float)game->window_height / (game->map_height * TILE_SIZE);
	else
		game->scale_y = 1.0;

	game->scale_x = game->scale_y = (game->scale_x < game->scale_y) ? 
		game->scale_x : game->scale_y;

	int offset_x = (game->window_width - (game->map_width * TILE_SIZE * game->scale_x)) / 2;
	int offset_y = (game->window_height - (game->map_height * TILE_SIZE * game->scale_y)) / 2;

	// Renderizar el mapa
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			pos_x = offset_x + x * TILE_SIZE * game->scale_x;
			pos_y = offset_y + y * TILE_SIZE * game->scale_y;

			// Dibujar el suelo primero
			put_image_to_buffer(buffer_data, game->img_floor, pos_x, pos_y,
				game->window_width, game->scale_x);

			// Dibujar otros elementos encima
			img_to_render = NULL;
			if (game->map[y][x] == WALL)
				img_to_render = game->img_wall;
			else if (game->map[y][x] == COLLECT)
				img_to_render = game->img_collect;
			else if (game->map[y][x] == EXIT)
				img_to_render = game->img_exit;
			else if (game->map[y][x] == PLAYER)
				img_to_render = game->player_anim ? 
					game->player_anim->frames[game->player_anim->current] : 
					game->img_player;

			if (img_to_render)
				put_image_to_buffer(buffer_data, img_to_render, pos_x, pos_y,
					game->window_width, game->scale_x);
			x++;
		}
		y++;
	}

	// Renderizar enemigos
	render_enemies(game);

	// Mostrar el buffer
	mlx_put_image_to_window(game->mlx, game->win, game->back_buffer, 0, 0);

	// Renderizar HUD y actualizar enemigos
	render_hud(game);
	move_enemies(game);

	return (1);
}

void	render_hud(t_game *game)
{
	char moves_str[50];
	char collect_str[50];
	char level_str[50];
	int bar_width = 120;
	int bar_height = 20;
	int progress;
	int hud_x = 5;
	int hud_y = 5;
	int text_spacing = 15;
	
	if (!game || !game->mlx || !game->win)
	{
		ft_putendl_fd("Error: Punteros nulos en render_hud", 2);
		return;
	}
	
	// Fondo semi-transparente para el HUD
	for (int i = 0; i < bar_width + 20; i++)
		for (int j = 0; j < bar_height + 45; j++)
			mlx_pixel_put(game->mlx, game->win, i + hud_x, j + hud_y, 0x55000000);
	
	snprintf(moves_str, sizeof(moves_str), "Moves: %d", game->moves);
	mlx_string_put(game->mlx, game->win, hud_x + 5, hud_y + text_spacing, 0xFFFFFF, moves_str);
	
	snprintf(collect_str, sizeof(collect_str), "Collected: %d/%d",
		game->collected, game->collectibles);
	mlx_string_put(game->mlx, game->win, hud_x + 5, hud_y + text_spacing * 2, 0xFFFFFF, collect_str);
	
	// Barra de progreso
	progress = (game->collected * bar_width) / game->collectibles;
	
	// Fondo de la barra
	for (int i = 0; i < bar_width; i++)
		mlx_pixel_put(game->mlx, game->win, i + hud_x + 5, hud_y + text_spacing * 3, 0x444444);
	
	// Progreso
	for (int i = 0; i < progress; i++)
		mlx_pixel_put(game->mlx, game->win, i + hud_x + 5, hud_y + text_spacing * 3, 0x00FF00);
	
	// Añadir nivel actual
	snprintf(level_str, sizeof(level_str), "Level: %d", game->current_level);
	mlx_string_put(game->mlx, game->win, hud_x + 5, hud_y + text_spacing * 4, 0xFFFFFF, level_str);
}
