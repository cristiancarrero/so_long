/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#           */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/game.h"
#include <mlx.h>

void debug_game_state(t_game *game)
{
    ft_putendl_fd("\nEstado del juego:", 1);
    ft_putstr_fd("Estado: ", 1);
    ft_putnbr_fd(game->state, 1);
    ft_putchar_fd('\n', 1);
    ft_putstr_fd("Posición del jugador: (", 1);
    ft_putnbr_fd(game->player.x, 1);
    ft_putstr_fd(",", 1);
    ft_putnbr_fd(game->player.y, 1);
    ft_putendl_fd(")", 1);
    ft_putstr_fd("Coleccionables: ", 1);
    ft_putnbr_fd(game->collected, 1);
    ft_putstr_fd("/", 1);
    ft_putnbr_fd(game->collectibles, 1);
    ft_putchar_fd('\n', 1);
}

int	init_game(t_game *game)
{
	ft_putendl_fd("Inicializando MLX...", 1);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putendl_fd("Error: No se pudo inicializar MLX", 2);
		return (0);
	}
	ft_putendl_fd("MLX inicializado correctamente", 1);
	
	// Inicializar valores por defecto
	game->win = NULL;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->moves = 0;
	game->collectibles = 0;
	game->collected = 0;
	game->state = STATE_MENU;
	
	// Inicializar punteros de imágenes a NULL
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_player = NULL;
	game->img_collect = NULL;
	game->img_exit = NULL;
	game->back_buffer = NULL;
	game->player.sprite_left = NULL;
	game->player.sprite_right = NULL;
	
	return (1);
}

int	load_game(t_game *game, char *map_path)
{
	ft_putendl_fd("Intentando parsear mapa...", 1);
	if (!parse_map(game, map_path))
	{
		print_error(ERR_MAP);
		return (0);
	}

	ft_putendl_fd("Validando mapa...", 1);
	if (!validate_map(game))
	{
		print_error("Error al validar el mapa");
		free_map(game->map);
		game->map = NULL;
		return (0);
	}

	if (!load_images(game))
	{
		print_error(ERR_IMG);
		free_game(game);
		return (0);
	}

	init_player(game);

	// Calcular dimensiones de la ventana basadas en el mapa
	game->window_width = game->map_width * TILE_SIZE;
	game->window_height = game->map_height * TILE_SIZE;

	// Asegurarnos de que la ventana no sea demasiado pequeña
	if (game->window_width < WINDOW_WIDTH)
		game->window_width = WINDOW_WIDTH;
	if (game->window_height < WINDOW_HEIGHT)
		game->window_height = WINDOW_HEIGHT;

	ft_putendl_fd("\nCreando ventana...", 1);
	game->win = mlx_new_window(game->mlx, game->window_width, game->window_height, WINDOW_TITLE);
	if (!game->win)
	{
		print_error(ERR_WIN);
		free_game(game);
		return (0);
	}
	ft_putendl_fd("Ventana creada correctamente", 1);

	printf("Window created, setting up hooks...\n");
	setup_hooks(game);
	printf("Hooks setup complete\n");

	game->state = STATE_PLAYING;
	game->moves = 0;
	game->collected = 0;

	// Realizar el primer renderizado
	if (!render_game(game))
	{
		print_error("Error al renderizar el juego");
		free_game(game);
		return (0);
	}

	debug_game_state(game);

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

	ft_putstr_fd("Cargando floor: ", 1);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, SPRITE_FLOOR, &width, &height);
	if (!game->img_floor)
	{
		ft_putendl_fd("Error cargando floor", 2);
		return (0);
	}
	ft_putendl_fd("OK", 1);

	ft_putstr_fd("Cargando wall: ", 1);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, SPRITE_WALL, &width, &height);
	if (!game->img_wall)
	{
		ft_putendl_fd("Error cargando wall", 2);
		return (0);
	}
	make_transparent(game->img_wall);
	ft_putendl_fd("OK", 1);

	ft_putstr_fd("Cargando player: ", 1);
	game->img_player = mlx_xpm_file_to_image(game->mlx, SPRITE_PLAYER, &width, &height);
	if (!game->img_player)
	{
		ft_putendl_fd("Error cargando player", 2);
		return (0);
	}
	make_transparent(game->img_player);
	ft_putendl_fd("OK", 1);

	ft_putstr_fd("Cargando collect: ", 1);
	game->img_collect = mlx_xpm_file_to_image(game->mlx, SPRITE_COLLECT, &width, &height);
	if (!game->img_collect)
	{
		ft_putendl_fd("Error cargando collect", 2);
		return (0);
	}
	make_transparent(game->img_collect);
	ft_putendl_fd("OK", 1);

	ft_putstr_fd("Cargando exit: ", 1);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, SPRITE_EXIT, &width, &height);
	if (!game->img_exit)
	{
		ft_putendl_fd("Error cargando exit", 2);
		return (0);
	}
	make_transparent(game->img_exit);
	ft_putendl_fd("OK", 1);

	return (1);
}

void	make_transparent(void *img)
{
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*data;
	int		i;
	int		total_size;

	data = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	total_size = size_line * TILE_SIZE;
	i = 0;
	while (i < total_size)
	{
		unsigned int *color = (unsigned int *)(data + i);
		if ((*color & 0xFFFFFF) == 0)
			*color = 0;
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