/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game_bonus.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <signal.h>

void	make_transparent(void *img);

int	init_game(t_game *game)
{
	// Inicializar valores a NULL/0
	ft_memset(game, 0, sizeof(t_game));
	
	// Inicializar MLX
	game->mlx = mlx_init();
	if (!game->mlx)
		return (error_handler("Error\nNo se pudo inicializar MLX"));

	// Inicializar otros valores
	game->state = STATE_PLAYING;
	game->scale_x = 1.0;
	game->scale_y = 1.0;
	game->moves = 0;
	game->collected = 0;

	return (1);
}

int	load_game(t_game *game, char *map_path)
{
	char *full_path;

	if (!game || !game->mlx)
	{
		ft_putendl_fd("Error: Juego no inicializado correctamente", 2);
		return (0);
	}

	if (ft_strncmp(map_path, "bonus/maps/", 11) != 0)
	{
		full_path = ft_strjoin("bonus/maps/", map_path + 5);  // +5 para saltar "maps/"
		if (!full_path)
			return (0);
	}
	else
		full_path = ft_strdup(map_path);

	ft_putendl_fd("Intentando parsear mapa...", 1);
	if (!parse_map(game, full_path))
	{
		ft_putendl_fd("Error al parsear el mapa", 2);
		free(full_path);
		return (0);
	}
	free(full_path);

	ft_putendl_fd("Validando mapa...", 1);
	if (!validate_map(game))
	{
		ft_putendl_fd("Error al validar el mapa", 2);
		free_map(game->map);
		return (0);
	}

	ft_putendl_fd("Creando ventana...", 1);
	game->window_width = game->map_width * TILE_SIZE;
	game->window_height = game->map_height * TILE_SIZE;

	if (game->window_width <= 0 || game->window_height <= 0)
	{
		ft_putendl_fd("Error: Dimensiones de ventana inválidas", 2);
		free_map(game->map);
		return (0);
	}

	ft_putendl_fd("Cargando imágenes...", 1);
	if (!load_images(game))
	{
		ft_putendl_fd("Error al cargar imágenes", 2);
		free_game(game);
		return (0);
	}

	game->win = mlx_new_window(game->mlx, game->window_width, game->window_height, "so_long bonus");
	if (!game->win)
	{
		ft_putendl_fd("Error al crear la ventana", 2);
		free_game(game);
		return (0);
	}

	// Configurar los hooks de eventos
	setup_hooks(game);

	// Renderizar el juego inicial
	if (!render_game(game))
	{
		ft_putendl_fd("Error al renderizar el juego", 2);
		free_game(game);
		return (0);
	}

	return (1);
}

int	load_images(t_game *game)
{
	int	width;
	int	height;

	if (!game || !game->mlx)
	{
		ft_putendl_fd("Error: MLX no inicializado", 2);
		return (0);
	}

	ft_putendl_fd("Verificando archivos XPM...", 1);

	char *sprites[] = {SPRITE_WALL, SPRITE_FLOOR, SPRITE_PLAYER, SPRITE_COLLECT, SPRITE_EXIT};
	char *names[] = {"wall", "floor", "player", "collect", "exit"};

	for (int i = 0; i < 5; i++)
	{
		ft_putstr_fd("Verificando ", 1);
		ft_putstr_fd(names[i], 1);
		ft_putstr_fd(".xpm: ", 1);

		if (access(sprites[i], F_OK) == -1)
		{
			ft_putendl_fd("No existe", 2);
			ft_putstr_fd("Ruta completa: ", 2);
			char cwd[1024];
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				ft_putstr_fd(cwd, 2);
				ft_putchar_fd('/', 2);
				ft_putendl_fd(sprites[i], 2);
			}
			return (0);
		}
		else if (access(sprites[i], R_OK) == -1)
		{
			ft_putendl_fd("Sin permisos de lectura", 2);
			return (0);
		}
		else
		{
			ft_putendl_fd("OK", 1);
		}
	}

	ft_putendl_fd("Archivos XPM encontrados, cargando...", 1);

	game->img_wall = mlx_xpm_file_to_image(game->mlx, SPRITE_WALL, &width, &height);
	if (!game->img_wall)
	{
		ft_putendl_fd("Error: No se pudo cargar wall.xpm", 2);
		return (0);
	}

	game->img_floor = mlx_xpm_file_to_image(game->mlx, SPRITE_FLOOR, &width, &height);
	if (!game->img_floor)
	{
		ft_putendl_fd("Error: No se pudo cargar floor.xpm", 2);
		return (0);
	}

	game->img_player = mlx_xpm_file_to_image(game->mlx, SPRITE_PLAYER, &width, &height);
	if (!game->img_player)
	{
		ft_putendl_fd("Error: No se pudo cargar player.xpm", 2);
		return (0);
	}

	game->img_collect = mlx_xpm_file_to_image(game->mlx, SPRITE_COLLECT, &width, &height);
	if (!game->img_collect)
	{
		ft_putendl_fd("Error: No se pudo cargar collect.xpm", 2);
		return (0);
	}

	game->img_exit = mlx_xpm_file_to_image(game->mlx, SPRITE_EXIT, &width, &height);
	if (!game->img_exit)
	{
		ft_putendl_fd("Error: No se pudo cargar exit.xpm", 2);
		return (0);
	}

	// Cargar imágenes de enemigos
	if (!load_enemy_images(game))
	{
		ft_putendl_fd("Error al cargar imágenes de enemigos", 2);
		return (0);
	}

	ft_putendl_fd("Todas las imágenes cargadas correctamente", 1);
	debug_print_images(game);
	return (1);
}

void make_transparent(void *img)
{
	int     bits_per_pixel;
	int     size_line;
	int     endian;
	char    *data;
	int     i;

	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	i = 0;
	while (i < size_line * TILE_SIZE)
	{
		if (*(unsigned int*)(data + i) == 0xFF000000)
			*(unsigned int*)(data + i) = 0x0;
		i += 4;
	}
}

void	debug_print_images(t_game *game)
{
	ft_putendl_fd("\nEstado de las imágenes:", 1);
	ft_putstr_fd("Wall: ", 1);
	ft_putendl_fd(game->img_wall ? "Cargado" : "No cargado", 1);
	ft_putstr_fd("Floor: ", 1);
	ft_putendl_fd(game->img_floor ? "Cargado" : "No cargado", 1);
	ft_putstr_fd("Player: ", 1);
	ft_putendl_fd(game->img_player ? "Cargado" : "No cargado", 1);
	ft_putstr_fd("Collect: ", 1);
	ft_putendl_fd(game->img_collect ? "Cargado" : "No cargado", 1);
	ft_putstr_fd("Exit: ", 1);
	ft_putendl_fd(game->img_exit ? "Cargado" : "No cargado", 1);
}

void print_file_status(const char *path)
{
    ft_putstr_fd("Verificando ", 1);
    ft_putstr_fd((char *)path, 1);
    ft_putstr_fd(": ", 1);
    if (access(path, F_OK) == -1)
        ft_putendl_fd("No existe", 2);
    else if (access(path, R_OK) == -1)
        ft_putendl_fd("Sin permisos de lectura", 2);
    else
        ft_putendl_fd("OK", 1);
}

int load_enemy_images(t_game *game)
{
	int width;
	int height;

	ft_putendl_fd("Cargando imágenes de enemigos...", 1);

	if (!game->enemies || game->num_enemies <= 0)
		return (1);

	for (int i = 0; i < game->num_enemies; i++)
	{
		if (game->enemies[i].type == 1)  // Enemigo tipo 1 (estático)
		{
			game->enemies[i].current = mlx_xpm_file_to_image(game->mlx,
				"bonus/textures/enemy1/enemy1.xpm", &width, &height);
			if (!game->enemies[i].current)
			{
				ft_putendl_fd("Error: No se pudo cargar enemy1.xpm", 2);
				return (0);
			}
			game->enemies[i].sprites[0] = game->enemies[i].current;
		}
		else if (game->enemies[i].type == 2)  // Enemigo tipo 2 (animado)
		{
			// Cargar los frames de animación
			game->enemies[i].sprites[0] = mlx_xpm_file_to_image(game->mlx,
				"bonus/textures/enemy2/enemy1.xpm", &width, &height);
			game->enemies[i].sprites[1] = mlx_xpm_file_to_image(game->mlx,
				"bonus/textures/enemy2/enemy2.xpm", &width, &height);
			game->enemies[i].sprites[2] = mlx_xpm_file_to_image(game->mlx,
				"bonus/textures/enemy2/enemy3.xpm", &width, &height);
			
			if (!game->enemies[i].sprites[0] || !game->enemies[i].sprites[1] || 
				!game->enemies[i].sprites[2])
			{
				// Debug: Imprimir rutas completas
				char cwd[1024];
				if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
					ft_putstr_fd("Intentando cargar desde:\n", 2);
					ft_putstr_fd(cwd, 2);
					ft_putendl_fd("/bonus/textures/enemy2/enemy1.xpm", 2);
					ft_putstr_fd(cwd, 2);
					ft_putendl_fd("/bonus/textures/enemy2/enemy2.xpm", 2);
					ft_putstr_fd(cwd, 2);
					ft_putendl_fd("/bonus/textures/enemy2/enemy3.xpm", 2);
				}
				ft_putendl_fd("Error: No se pudieron cargar los sprites del enemigo tipo 2", 2);
				return (0);
			}
			game->enemies[i].current = game->enemies[i].sprites[0];
			game->enemies[i].frame = 0;
		}
	}
	
	ft_putendl_fd("Imágenes de enemigos cargadas correctamente", 1);
	return (1);
}