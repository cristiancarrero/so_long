#include "../../inc/game.h"

// Prototipos de funciones
void	put_sprite(t_game *game, void *sprite, int x, int y);
void	*flip_sprite_horizontally(t_game *game, void *original);
void	*scale_sprite(t_game *game, void *original);
void	render_player(t_game *game);
void	render_hud(t_game *game);
void	put_sprite_scaled(t_game *game, void *sprite, int x, int y, float scale);
void	put_sprite_margin(t_game *game, void *sprite, int x, int y, int margin_x, int margin_y);
void	render_victory_screen(t_game *game);

void	put_sprite(t_game *game, void *sprite, int x, int y)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*img_data;
	int		*buffer_data;
	int		sprite_size = 64;

	if (!game->back_buffer || !sprite)
		return;

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp,
			&size_line, &endian);
	img_data = (int *)mlx_get_data_addr(sprite, &bpp, &size_line, &endian);

	if (!buffer_data || !img_data)
		return;

	float scale = (float)TILE_SIZE / sprite_size;
	int offset_x = (game->window_width - (game->map_width * TILE_SIZE)) / 2;
	int offset_y = (game->window_height - (game->map_height * TILE_SIZE)) / 2;

	// Asegurar que los offsets no sean negativos
	offset_x = (offset_x < 0) ? 0 : offset_x;
	offset_y = (offset_y < 0) ? 0 : offset_y;

	int screen_x = x * TILE_SIZE + offset_x;
	int screen_y = y * TILE_SIZE + offset_y;

	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
		{
			if (screen_x + j >= 0 && screen_x + j < game->window_width &&
				screen_y + i >= 0 && screen_y + i < game->window_height)
			{
				int src_i = i / scale;
				int src_j = j / scale;
				if (src_i < sprite_size && src_j < sprite_size)
				{
					unsigned int color = img_data[src_i * (size_line / 4) + src_j];
					if (color != 0 && (color & 0x00FFFFFF) != 0)
						buffer_data[(screen_y + i) * game->window_width + (screen_x + j)] = color;
				}
			}
		}
	}
}

void	*flip_sprite_horizontally(t_game *game, void *original)
{
	t_img_data	img;
	void		*new_img;
	int			i;
	int			j;
	int			sprite_size;

	sprite_size = 64;  // Tamaño original del sprite
	new_img = mlx_new_image(game->mlx, sprite_size, sprite_size);  // Crear imagen del tamaño original
	if (!new_img)
		return (NULL);

	img.orig = (int *)mlx_get_data_addr(original, &img.bpp,
			&img.size_line, &img.endian);
	img.new = (int *)mlx_get_data_addr(new_img, &img.bpp,
			&img.size_line, &img.endian);
	if (!img.orig || !img.new)
	{
		mlx_destroy_image(game->mlx, new_img);
		return (NULL);
	}

	i = -1;
	while (++i < sprite_size)
	{
		j = -1;
		while (++j < sprite_size)
		{
			img.color = img.orig[i * (img.size_line / 4) + j];
			if (img.color != 0 && (img.color & 0x00FFFFFF) != 0)
				img.new[i * (img.size_line / 4) + (sprite_size - 1 - j)] = img.color;
		}
	}

	// Ahora escalamos la imagen volteada al tamaño final
	void *scaled_img = scale_sprite(game, new_img);
	mlx_destroy_image(game->mlx, new_img);
	return (scaled_img);
}

void	*scale_sprite(t_game *game, void *original)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*orig_data;
	int		*new_data;
	void	*new_img;
	int		new_size;
	int		orig_size_line;

	new_size = TILE_SIZE;
	new_img = mlx_new_image(game->mlx, new_size, new_size);
	if (!new_img)
		return (NULL);

	orig_data = (int *)mlx_get_data_addr(original, &bpp, &orig_size_line, &endian);
	new_data = (int *)mlx_get_data_addr(new_img, &bpp, &size_line, &endian);
	if (!orig_data || !new_data)
	{
		mlx_destroy_image(game->mlx, new_img);
		return (NULL);
	}

	for (int i = 0; i < new_size; i++)
	{
		for (int j = 0; j < new_size; j++)
		{
			int orig_x = j;
			int orig_y = i;
			unsigned int color = orig_data[orig_y * (orig_size_line / 4) + orig_x];
			new_data[i * (size_line / 4) + j] = color;
		}
	}

	return (new_img);
}

void	render_player(t_game *game)
{
	void	*sprite;

	sprite = game->img_player;
	if (game->player.direction == -1 && game->player.sprite_left)
		sprite = game->player.sprite_left;
	if (sprite)
		put_sprite(game, sprite, game->player.x, game->player.y);
}

void	render_victory_screen(t_game *game)
{
	// Oscurecer el fondo actual
	int *buffer_data;
	int bpp, size_line, endian;
	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp,
		&size_line, &endian);

	// Aplicar efecto de oscurecimiento al fondo
	for (int i = 0; i < game->window_height * game->window_width; i++)
	{
		unsigned int color = buffer_data[i];
		unsigned char r = ((color >> 16) & 0xFF) * 0.3;
		unsigned char g = ((color >> 8) & 0xFF) * 0.3;
		unsigned char b = (color & 0xFF) * 0.3;
		buffer_data[i] = (r << 16) | (g << 8) | b;
	}

	// Crear panel central negro
	int panel_width = 400;
	int panel_height = 200;
	int panel_x = (game->window_width - panel_width) / 2;
	int panel_y = (game->window_height - panel_height) / 2;

	// Dibujar panel negro semitransparente
	for (int y = 0; y < panel_height; y++)
	{
		for (int x = 0; x < panel_width; x++)
		{
			if (panel_x + x >= 0 && panel_x + x < game->window_width &&
				panel_y + y >= 0 && panel_y + y < game->window_height)
			{
				int pos = (panel_y + y) * game->window_width + (panel_x + x);
				buffer_data[pos] = 0x88000000;
			}
		}
	}

	mlx_put_image_to_window(game->mlx, game->win, game->back_buffer, 0, 0);

	// Calcular posiciones de texto
	int text_y = panel_y + 60;
	char victory_text[] = "¡NIVEL COMPLETADO!";
	char moves_text[50];
	char exit_text[] = "Presiona ESC para salir";

	snprintf(moves_text, sizeof(moves_text), 
		"Movimientos: %d", game->moves);

	// Renderizar título con brillo
	int title_x = panel_x + (panel_width - ft_strlen(victory_text) * 10) / 2;
	mlx_string_put(game->mlx, game->win,
		title_x + 1, text_y + 1, 0x222222, victory_text);
	mlx_string_put(game->mlx, game->win,
		title_x, text_y, 0xFFFF00, victory_text);

	// Renderizar contador de movimientos
	int moves_x = panel_x + (panel_width - ft_strlen(moves_text) * 10) / 2;
	mlx_string_put(game->mlx, game->win,
		moves_x, text_y + 50, 0xFFFFFF, moves_text);

	// Renderizar texto de salida
	int exit_x = panel_x + (panel_width - ft_strlen(exit_text) * 10) / 2;
	mlx_string_put(game->mlx, game->win,
		exit_x, text_y + 100, 0x888888, exit_text);
}

int	render_game(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->win)
		return (0);

	// Recrear el buffer
	if (game->back_buffer)
	{
		mlx_destroy_image(game->mlx, game->back_buffer);
		game->back_buffer = NULL;
	}

	game->back_buffer = mlx_new_image(game->mlx,
		game->window_width, game->window_height);
	if (!game->back_buffer)
        return (0);

	// Obtener el buffer
	int *buffer_data;
	int bpp, size_line, endian;
	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp,
		&size_line, &endian);
	
	// Rellenar el fondo
	for (int i = 0; i < game->window_height * game->window_width; i++)
		buffer_data[i] = 0x282828;

	// Calcular el factor de escala para ajustar el mapa a la pantalla
	float scale_x = (float)(game->window_width - 100) / (game->map_width * TILE_SIZE);
	float scale_y = (float)(game->window_height - 100) / (game->map_height * TILE_SIZE);
	float scale = (scale_x < scale_y) ? scale_x : scale_y;

	// Renderizar el mapa escalado (siempre)
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			put_sprite_scaled(game, game->img_floor, x, y, scale);
			if (game->map[y][x] == WALL)
				put_sprite_scaled(game, game->img_wall, x, y, scale);
			else if (game->map[y][x] == COLLECT)
				put_sprite_scaled(game, game->img_collect, x, y, scale);
			else if (game->map[y][x] == EXIT)
				put_sprite_scaled(game, game->img_exit, x, y, scale);
		}
	}

	// Renderizar jugador escalado
	void *sprite = (game->player.direction == 1) ?
		game->img_player : game->player.sprite_left;
	if (sprite)
		put_sprite_scaled(game, sprite, game->player.x, game->player.y, scale);

	// Si estamos en estado victoria, renderizar la pantalla de victoria
	if (game->state == STATE_VICTORY)
	{
		render_victory_screen(game);
		render_hud(game);
		return (1);
	}

	// Si no estamos en victoria, renderizado normal
	mlx_put_image_to_window(game->mlx, game->win, game->back_buffer, 0, 0);
    render_hud(game);

    return (1);
}

void	render_hud(t_game *game)
{
	char	info_str[100];
	int		bar_width = 200;
	int		bar_height = 20;
	int		padding = 10;
	int		text_y = 25;
	int		bar_y = 40;
	int		progress;
	int		*buffer_data;
	int		bpp;
	int		size_line;
	int		endian;

	// Centrar el HUD
	int		hud_x = (game->window_width - bar_width) / 2;

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp,
			&size_line, &endian);

	// Fondo semitransparente para el HUD
	for (int y = 0; y < bar_y + bar_height + padding; y++)
	{
		for (int x = hud_x - padding; x < hud_x + bar_width + padding; x++)
		{
			if (x >= 0 && x < game->window_width && y >= 0)
			{
				int pos = y * game->window_width + x;
				buffer_data[pos] = 0x44000000;
			}
		}
	}

	// Texto informativo
	snprintf(info_str, sizeof(info_str), "Moves: %d  -  Items: %d/%d",
		game->moves, game->collected, game->collectibles);
	mlx_string_put(game->mlx, game->win,
		hud_x + (bar_width - 150) / 2 + 1, text_y + 1, 0x44000000, info_str);
	mlx_string_put(game->mlx, game->win,
		hud_x + (bar_width - 150) / 2, text_y, 0xFFFFFF, info_str);

	// Barra de progreso
	progress = (game->collected * bar_width) / game->collectibles;

	// Fondo de la barra
	for (int x = 0; x < bar_width; x++)
	{
		for (int y = 0; y < bar_height; y++)
		{
			int pos = (bar_y + y) * game->window_width + (hud_x + x);
			buffer_data[pos] = 0x333333;  // Gris más oscuro para mejor contraste
		}
	}

	// Progreso de la barra con gradiente suavizado
	for (int x = 0; x < progress; x++)
	{
		float ratio = (float)x / bar_width;
		unsigned int green = 0x66 + (0x99 * ratio);  // Verde más suave
		unsigned int red = 0x33 + (0x66 * ratio);    // Rojo suave para mezclar
		unsigned int color = (red << 16) | (green << 8);  // Combinar colores

		for (int y = 0; y < bar_height; y++)
		{
			int pos = (bar_y + y) * game->window_width + (hud_x + x);
			buffer_data[pos] = color;
		}
	}
}

void	put_sprite_scaled(t_game *game, void *sprite, int x, int y, float scale)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*img_data;
	int		*buffer_data;
	int		sprite_size = 64;

	if (!game->back_buffer || !sprite)
		return;

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp,
			&size_line, &endian);
	img_data = (int *)mlx_get_data_addr(sprite, &bpp, &size_line, &endian);

	if (!buffer_data || !img_data)
		return;

	int scaled_tile = TILE_SIZE * scale;
	int offset_x = (game->window_width - (game->map_width * scaled_tile)) / 2;
	int offset_y = (game->window_height - (game->map_height * scaled_tile)) / 2;

	int screen_x = x * scaled_tile + offset_x;
	int screen_y = y * scaled_tile + offset_y;

	for (int i = 0; i < scaled_tile; i++)
	{
		for (int j = 0; j < scaled_tile; j++)
		{
			if (screen_x + j >= 0 && screen_x + j < game->window_width &&
				screen_y + i >= 0 && screen_y + i < game->window_height)
			{
				int src_i = (i * sprite_size) / scaled_tile;
				int src_j = (j * sprite_size) / scaled_tile;
				if (src_i < sprite_size && src_j < sprite_size)
				{
					unsigned int color = img_data[src_i * (size_line / 4) + src_j];
					if (color != 0 && (color & 0x00FFFFFF) != 0)
						buffer_data[(screen_y + i) * game->window_width + (screen_x + j)] = color;
				}
			}
		}
	}
}

void	put_sprite_margin(t_game *game, void *sprite, int x, int y, int margin_x, int margin_y)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		*img_data;
	int		*buffer_data;
	int		sprite_size = 64;

	if (!game->back_buffer || !sprite)
		return;

	buffer_data = (int *)mlx_get_data_addr(game->back_buffer, &bpp,
			&size_line, &endian);
	img_data = (int *)mlx_get_data_addr(sprite, &bpp, &size_line, &endian);

	if (!buffer_data || !img_data)
		return;

	float scale = (float)TILE_SIZE / sprite_size;
	int screen_x = x * TILE_SIZE + margin_x;
	int screen_y = y * TILE_SIZE + margin_y;

	for (int i = 0; i < TILE_SIZE; i++)
	{
		for (int j = 0; j < TILE_SIZE; j++)
		{
			if (screen_x + j >= 0 && screen_x + j < game->window_width &&
				screen_y + i >= 0 && screen_y + i < game->window_height)
			{
				int src_i = i / scale;
				int src_j = j / scale;
				if (src_i < sprite_size && src_j < sprite_size)
				{
					unsigned int color = img_data[src_i * (size_line / 4) + src_j];
					if (color != 0 && (color & 0x00FFFFFF) != 0)
						buffer_data[(screen_y + i) * game->window_width + (screen_x + j)] = color;
				}
			}
		}
	}
} 