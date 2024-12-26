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

static int	init_game_vars(t_game *game)
{
	int	i;

	game->collected = 0;
	game->moves = 0;
	game->is_facing_left = 0;
	game->frame_count = 0;
	game->anim_frame_count = 0;
	game->current_frame = 0;
	game->mlx = NULL;
	game->win = NULL;
	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		init_img(&game->enemy[i]);
		game->enemy[i].img = NULL;
		i++;
	}
	init_img(&game->player);
	init_img(&game->wall);
	init_img(&game->floor);
	init_img(&game->collect);
	init_img(&game->exit);
	init_img(&game->buffer);
	return (1);
}

static int	init_window(t_game *game)
{
	ft_putstr_fd("Inicializando MLX...\n", 1);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error: No se pudo inicializar MLX\n", 1);
		return (0);
	}
	ft_putstr_fd("MLX inicializado correctamente\n", 1);

	ft_putstr_fd("Creando ventana...\n", 1);
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE, "so_long bonus");
	if (!game->win)
	{
		ft_putstr_fd("Error: No se pudo crear la ventana\n", 1);
		return (0);
	}
	ft_putstr_fd("Ventana creada correctamente\n", 1);

	ft_putstr_fd("Creando buffer de imagen...\n", 1);
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;
	game->buffer.img = mlx_new_image(game->mlx,
			game->buffer.width,
			game->buffer.height);
	if (!game->buffer.img)
	{
		ft_putstr_fd("Error: No se pudo crear el buffer de imagen\n", 1);
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
	ft_putstr_fd("Buffer de imagen creado correctamente\n", 1);
	ft_putstr_fd("Dimensiones del buffer: ", 1);
	ft_putnbr_fd(game->buffer.width, 1);
	ft_putstr_fd("x", 1);
	ft_putnbr_fd(game->buffer.height, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

void	init_hud(t_game *game)
{
	init_img(&game->buffer);
	game->buffer.img = mlx_new_image(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE);
	if (!game->buffer.img)
	{
		ft_putstr_fd("Error: No se pudo crear el buffer del HUD\n", 1);
		return ;
	}
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length,
			&game->buffer.endian);
	if (!game->buffer.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección del buffer\n", 1);
		mlx_destroy_image(game->mlx, game->buffer.img);
		game->buffer.img = NULL;
		return ;
	}
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;
}

int	init_game(t_game *game, char *map_path)
{
	if (!read_map(map_path, game))
		return (0);
	if (!check_map_size_and_chars(game))
		return (0);
	if (!check_rectangular(game))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!check_characters(game))
		return (0);
	if (!init_game_vars(game))
		return (0);
	if (!init_window(game))
		return (0);
	if (!load_textures(game))
		return (0);
	
	// Contar enemigos antes de cargar sus texturas
	int x, y, enemy_count = 0;
	for (y = 0; y < game->map_height; y++)
		for (x = 0; x < game->map_width; x++)
			if (game->map[y][x] == 'N' || game->map[y][x] == 'M')
				enemy_count++;
	
	game->num_enemies = enemy_count;
	ft_putstr_fd("Número de enemigos encontrados: ", 1);
	ft_putnbr_fd(enemy_count, 1);
	ft_putstr_fd("\n", 1);

	if (enemy_count > 0)
	{
		if (!load_enemy_textures(game))
			return (0);
		init_enemies(game);
	}
	init_hud(game);
	return (1);
}
