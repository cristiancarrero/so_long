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

#include "../inc/game_bonus.h"
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

int	render_game(t_game *game)
{
	ft_putendl_fd("\n=== Iniciando render_game ===", 1);
	static int render_count = 0;
	int	x;
	int	y;
	int	pos_x;
	int	pos_y;
	void	*img_to_render;
	int		*buffer_data;
	int		bpp;
	int		size_line;
	int		endian;

	ft_putstr_fd("\nDebug: Iniciando render #", 1);
	ft_putnbr_fd(++render_count, 1);
	ft_putchar_fd('\n', 1);

	if (!game || !game->mlx || !game->win || !game->map)
	{
		ft_putstr_fd("Error: Punteros nulos en render_game - game: ", 2);
		ft_putnbr_fd((int)(game != NULL), 2);
		if (game)
		{
			ft_putstr_fd(", mlx: ", 2);
			ft_putnbr_fd((int)(game->mlx != NULL), 2);
			ft_putstr_fd(", win: ", 2);
			ft_putnbr_fd((int)(game->win != NULL), 2);
			ft_putstr_fd(", map: ", 2);
			ft_putnbr_fd((int)(game->map != NULL), 2);
		}
		ft_putchar_fd('\n', 2);
		return (0);
	}

	if (!game->img_floor || !game->img_wall || !game->img_player || 
		!game->img_collect || !game->img_exit)
	{
		ft_putendl_fd("Error: Imágenes no cargadas correctamente", 2);
		return (0);
	}

	ft_putstr_fd("Debug: Dimensiones del mapa: ", 1);
	ft_putnbr_fd(game->map_width, 1);
	ft_putstr_fd("x", 1);
	ft_putnbr_fd(game->map_height, 1);
	ft_putchar_fd('\n', 1);

	// Asegurarnos de que tenemos un buffer válido
	ft_putendl_fd("Verificando buffer...", 1);
	if (!game->back_buffer)
	{
		ft_putendl_fd("Creando nuevo buffer...", 1);
		game->back_buffer = mlx_new_image(game->mlx, game->window_width, game->window_height);
		if (!game->back_buffer)
		{
			ft_putendl_fd("Error: No se pudo crear el buffer", 2);
			return (0);
		}
		ft_putendl_fd("Buffer creado correctamente", 1);
	}

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp, &size_line, &endian);
	if (!buffer_data)
	{
		ft_putendl_fd("Error: No se pudo obtener la dirección del buffer", 2);
		return (0);
	}
	ft_putendl_fd("Dirección del buffer obtenida", 1);

	// Limpiar el buffer
	ft_putendl_fd("Limpiando buffer...", 1);
	for (int i = 0; i < game->window_height; i++)
	{
		ft_memset(buffer_data + (i * size_line / 4), 0, size_line);
	}
	ft_putendl_fd("Buffer limpiado", 1);

	ft_putstr_fd("Dimensiones de ventana: ", 1);
	ft_putnbr_fd(game->window_width, 1);
	ft_putstr_fd("x", 1);
	ft_putnbr_fd(game->window_height, 1);
	ft_putchar_fd('\n', 1);

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

	ft_putstr_fd("Escala: ", 1);
	ft_putnbr_fd((int)(game->scale_x * 100), 1);
	ft_putstr_fd("% x ", 1);
	ft_putnbr_fd((int)(game->scale_y * 100), 1);
	ft_putstr_fd("%\n", 1);

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (y >= game->map_height || x >= game->map_width)
			{
				ft_putendl_fd("Error: Índices fuera de rango", 2);
				return (0);
			}

			pos_x = offset_x + x * TILE_SIZE * game->scale_x;
			pos_y = offset_y + y * TILE_SIZE * game->scale_y;

			ft_putstr_fd("Renderizando en (", 1);
			ft_putnbr_fd(x, 1);
			ft_putstr_fd(",", 1);
			ft_putnbr_fd(y, 1);
			ft_putstr_fd("): ", 1);

			// Dibujar en el buffer en lugar de la ventana
			put_image_to_buffer(buffer_data, game->img_floor, pos_x, pos_y,
				game->window_width, game->scale_x);

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

			ft_putchar_fd(game->map[y][x], 1);
			ft_putchar_fd('\n', 1);

			if (img_to_render)
			{
				// Dibujar en el buffer en lugar de la ventana
				put_image_to_buffer(buffer_data, img_to_render, pos_x, pos_y,
					game->window_width, game->scale_x);
			}
			x++;
		}
		y++;
	}

	// Mostrar el buffer completo de una vez
	ft_putendl_fd("Mostrando buffer en ventana...", 1);
	mlx_put_image_to_window(game->mlx, game->win, game->back_buffer, 0, 0);
	ft_putendl_fd("Buffer mostrado", 1);

	// Renderizar enemigos después de mostrar el buffer
	if (game->img_enemy)  // Verificar que la imagen del enemigo existe
	{
		ft_putendl_fd("Iniciando renderizado de enemigos...", 1);
		for (int i = 0; i < game->num_enemies; i++)
		{
			ft_putstr_fd("Renderizando enemigo ", 1);
			ft_putnbr_fd(i, 1);
			ft_putchar_fd('\n', 1);
			int pos_x = offset_x + game->enemies[i].pos.x * TILE_SIZE * game->scale_x;
			int pos_y = offset_y + game->enemies[i].pos.y * TILE_SIZE * game->scale_y;
			mlx_put_image_to_window(game->mlx, game->win, game->img_enemy,
				pos_x, pos_y);
		}
		ft_putendl_fd("Renderizado de enemigos completado", 1);
	}

	ft_putendl_fd("Debug: Renderizado del mapa completado", 1);
	render_hud(game);
	ft_putendl_fd("Debug: HUD renderizado", 1);

	ft_putendl_fd("Moviendo enemigos...", 1);
	move_enemies(game);
	ft_putendl_fd("Movimiento de enemigos completado", 1);
	ft_putendl_fd("=== render_game completado ===\n", 1);
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
