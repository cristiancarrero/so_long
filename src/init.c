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

#include "../inc/game.h"
#include "../libft/libft.h"
#include <unistd.h>

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
	game->map_width = 0;
	game->map_height = 0;
	game->window_width = 640;
	game->window_height = 480;
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

	ft_putendl_fd("MLX inicializado correctamente", 1);
	return (1);
}

int	load_game(t_game *game, char *map_path)
{
	if (!game || !game->mlx)
	{
		ft_putendl_fd("Error: Juego no inicializado correctamente", 2);
		return (0);
	}

	ft_putendl_fd("Intentando parsear mapa...", 1);
	if (!parse_map(game, map_path))
	{
		ft_putendl_fd("Error al parsear el mapa", 2);
		return (0);
	}

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
	
	ft_putendl_fd("Cargando imágenes...", 1);
	
	game->img_wall = mlx_xpm_file_to_image(game->mlx, SPRITE_WALL, &width, &height);
	if (!game->img_wall)
	{
		ft_putendl_fd("Error cargando wall.xpm", 2);
		return (0);
	}
	
	game->img_floor = mlx_xpm_file_to_image(game->mlx, SPRITE_FLOOR, &width, &height);
	if (!game->img_floor)
	{
		ft_putendl_fd("Error cargando floor.xpm", 2);
		return (0);
	}
	
	game->img_player = mlx_xpm_file_to_image(game->mlx, SPRITE_PLAYER, &width, &height);
	if (!game->img_player)
	{
		ft_putendl_fd("Error cargando player.xpm", 2);
		return (0);
	}
	
	game->img_collect = mlx_xpm_file_to_image(game->mlx, SPRITE_COLLECT, &width, &height);
	if (!game->img_collect)
	{
		ft_putendl_fd("Error cargando collect.xpm", 2);
		return (0);
	}
	
	game->img_exit = mlx_xpm_file_to_image(game->mlx, SPRITE_EXIT, &width, &height);
	if (!game->img_exit)
	{
		ft_putendl_fd("Error cargando exit.xpm", 2);
		return (0);
	}
	
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
		unsigned int color = *(unsigned int*)(data + i);
		// Comprobar si el color es negro o casi negro
		if ((color & 0x00FFFFFF) == 0 || color == 0xFF000000)
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