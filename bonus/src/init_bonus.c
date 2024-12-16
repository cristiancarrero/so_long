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
	// Verificar si ya hay una instancia de MLX
	void *test_mlx = mlx_init();
	if (test_mlx)
	{
		mlx_destroy_display(test_mlx);
		free(test_mlx);
	}

	// Asegurarnos de que las señales no están bloqueadas
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_UNBLOCK, &set, NULL);

	ft_putendl_fd("Iniciando MLX...", 1);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putendl_fd("Error: No se pudo inicializar MLX", 2);
		return (0);
	}

	game->win = NULL;
	game->map = NULL;
	game->back_buffer = NULL;
	game->img_enemy = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->window_width = 640;  // Tamaño inicial de la ventana
	game->window_height = 480; // Tamaño inicial de la ventana
	game->scale_x = 1.0;
	game->scale_y = 1.0;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_player = NULL;
	game->img_collect = NULL;
	game->img_exit = NULL;
	game->player.x = 0;
	game->player.y = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->moves = 0;
	game->exit_found = 0;
	game->player_found = 0;
	game->state = STATE_PLAYING;
	game->player_anim = NULL;
	game->collect_anim = NULL;
	game->current_level = 1;
	game->max_levels = 3;
	game->enemies = NULL;
	game->num_enemies = 0;

	// Inicializar rutas de niveles
	game->level_paths = malloc(sizeof(char *) * (MAX_LEVELS + 1));
	if (!game->level_paths)
		return (0);

	ft_putendl_fd("Inicializando rutas de niveles:", 1);
	game->level_paths[0] = ft_strdup("bonus/maps/map1.ber");
	ft_putstr_fd("Nivel 1: ", 1);
	ft_putendl_fd(game->level_paths[0], 1);

	game->level_paths[1] = ft_strdup("bonus/maps/map2.ber");
	ft_putstr_fd("Nivel 2: ", 1);
	ft_putendl_fd(game->level_paths[1], 1);

	game->level_paths[2] = ft_strdup("bonus/maps/map3.ber");
	ft_putstr_fd("Nivel 3: ", 1);
	ft_putendl_fd(game->level_paths[2], 1);

	game->level_paths[3] = NULL;

	// Verificar que todos los paths se crearon correctamente
	for (int i = 0; i < game->max_levels; i++)
	{
		if (!game->level_paths[i])
		{
			ft_putendl_fd("Error: No se pudo inicializar la ruta del nivel", 2);
			return (0);
		}
	}

	ft_putendl_fd("MLX inicializado correctamente", 1);

	game->player_anim = load_animation(game, "./bonus/textures/player/player", PLAYER_FRAMES);
	game->collect_anim = load_animation(game, "./bonus/textures/collect/collect", COLLECT_FRAMES);

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

	ft_putstr_fd("Dimensiones del mapa: ", 1);
	ft_putnbr_fd(game->map_width, 1);
	ft_putstr_fd("x", 1);
	ft_putnbr_fd(game->map_height, 1);
	ft_putchar_fd('\n', 1);

	game->win = mlx_new_window(game->mlx, game->window_width,
			game->window_height, WINDOW_TITLE);
	if (!game->win)
	{
		ft_putendl_fd("Error al crear la ventana", 2);
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

	// Configurar los hooks de eventos
	setup_hooks(game);

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

	game->img_enemy = mlx_xpm_file_to_image(game->mlx, "./bonus/textures/enemy.xpm", &width, &height);
	if (!game->img_enemy)
	{
		ft_putendl_fd("Error: No se pudo cargar enemy.xpm", 2);
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