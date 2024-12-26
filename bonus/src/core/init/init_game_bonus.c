/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_game_vars(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_height = 0;
	game->map_width = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->num_enemies = 0;
	game->is_facing_left = 0;
	game->frame_count = 0;
	game->enemy_move_count = 0;
	game->anim_frame_count = 0;
	game->current_frame = 0;
}

static int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error: No se pudo inicializar MLX\n", 1);
		return (0);
	}
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long bonus");
	if (!game->win)
	{
		ft_putstr_fd("Error: No se pudo crear la ventana\n", 1);
		return (0);
	}
	return (1);
}

static int	init_buffer(t_game *game)
{
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;
	game->buffer.img = mlx_new_image(game->mlx,
			game->buffer.width, game->buffer.height);
	if (!game->buffer.img)
	{
		ft_putstr_fd("Error: No se pudo crear el buffer\n", 1);
		return (0);
	}
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length,
			&game->buffer.endian);
	if (!game->buffer.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección del buffer\n", 1);
		return (0);
	}
	return (1);
}

static int	read_map_line(int fd, t_game *game, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
		return (0);
	if (game->map_width == 0)
		game->map_width = ft_strlen(*line) - 1;
	return (1);
}

static int	process_map_line(t_game *game, char *line)
{
	char	*tmp;
	int		i;

	if (!line)
		return (0);
	tmp = ft_strtrim(line, "\n");
	free(line);
	if (!tmp)
		return (0);
	game->map[game->map_height] = malloc(sizeof(char) * (game->map_width + 1));
	if (!game->map[game->map_height])
	{
		free(tmp);
		return (0);
	}
	i = -1;
	while (tmp[++i] && i < game->map_width)
		game->map[game->map_height][i] = tmp[i];
	game->map[game->map_height][i] = '\0';
	free(tmp);
	game->map_height++;
	return (1);
}

static int	count_map_lines(char *file)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		lines++;
	}
	close(fd);
	return (lines);
}

static int	allocate_map(t_game *game, char *file)
{
	int	total_lines;

	total_lines = count_map_lines(file);
	if (total_lines <= 0)
		return (0);
	game->map = malloc(sizeof(char *) * (total_lines + 1));
	if (!game->map)
		return (0);
	game->map[total_lines] = NULL;
	return (1);
}

static int	read_map_file(t_game *game, char *file)
{
	int		fd;
	char	*line;

	if (!allocate_map(game, file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read_map_line(fd, game, &line))
	{
		if (!process_map_line(game, line))
		{
			close(fd);
			return (0);
		}
	}
	close(fd);
	return (1);
}

static int	init_enemies_count(t_game *game)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
			if (game->map[y][x] == 'N' || game->map[y][x] == 'M')
				count++;
	}
	game->num_enemies = count;
	return (count);
}

static int	init_enemies_array(t_game *game)
{
	int	x;
	int	y;
	int	enemy_index;

	enemy_index = 0;
	y = -1;
	while (++y < game->map_height)
	{
		x = -1;
		while (++x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'M')
			{
				if (enemy_index >= MAX_ENEMIES)
					return (0);
				game->enemies[enemy_index].x = x;
				game->enemies[enemy_index].y = y;
				game->enemies[enemy_index].type = game->map[y][x];
				game->enemies[enemy_index].direction = 1;
				enemy_index++;
			}
		}
	}
	return (1);
}

int	init_game(t_game *game, char *file)
{
	ft_putstr_fd("\n=== Iniciando el juego ===\n", 1);
	init_game_vars(game);
	ft_putstr_fd("Variables del juego inicializadas\n", 1);
	
	if (!read_map_file(game, file))
	{
		ft_putstr_fd("Error: No se pudo leer el mapa\n", 1);
		return (0);
	}
	ft_putstr_fd("Mapa leído correctamente\n", 1);
	
	if (!validate_map(game))
	{
		ft_putstr_fd("Error: Validación del mapa fallida\n", 1);
		return (0);
	}
	ft_putstr_fd("Mapa validado correctamente\n", 1);
	
	if (!init_window(game))
	{
		ft_putstr_fd("Error: Inicialización de ventana fallida\n", 1);
		return (0);
	}
	ft_putstr_fd("Ventana inicializada correctamente\n", 1);
	
	if (!init_buffer(game))
	{
		ft_putstr_fd("Error: Inicialización de buffer fallida\n", 1);
		return (0);
	}
	ft_putstr_fd("Buffer inicializado correctamente\n", 1);
	
	if (!load_textures(game))
	{
		ft_putstr_fd("Error: Carga de texturas fallida\n", 1);
		return (0);
	}
	ft_putstr_fd("Texturas base cargadas correctamente\n", 1);
	
	int enemy_count = init_enemies_count(game);
	ft_putstr_fd("Número de enemigos encontrados: ", 1);
	ft_putnbr_fd(enemy_count, 1);
	ft_putstr_fd("\n", 1);
	
	if (enemy_count > 0)
	{
		ft_putstr_fd("Intentando cargar texturas de enemigos...\n", 1);
		if (!load_enemy_textures(game))
		{
			ft_putstr_fd("Error: Carga de texturas de enemigos fallida\n", 1);
			return (0);
		}
		ft_putstr_fd("Texturas de enemigos cargadas correctamente\n", 1);
		ft_putstr_fd("Inicializando array de enemigos...\n", 1);
		if (!init_enemies_array(game))
		{
			ft_putstr_fd("Error: No se pudo inicializar el array de enemigos\n", 1);
			return (0);
		}
		ft_putstr_fd("Array de enemigos inicializado correctamente\n", 1);
	}
	
	ft_putstr_fd("=== Inicialización completada con éxito ===\n\n", 1);
	return (1);
}
