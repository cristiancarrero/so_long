/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/so_long.h"

static void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

static void	create_mirrored_player(t_game *game, int width, int height)
{
	void	*new_img;
	char	*src;
	char	*dst;
	int		x;
	int		y;

	new_img = mlx_new_image(game->mlx, width, height);
	if (!new_img)
		return ;
	game->player_left.img = new_img;
	game->player_left.addr = mlx_get_data_addr(new_img,
			&game->player_left.bits_per_pixel,
			&game->player_left.line_length,
			&game->player_left.endian);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			src = game->player.addr + (y * game->player.line_length
					+ (width - 1 - x) * (game->player.bits_per_pixel / 8));
			dst = game->player_left.addr + (y * game->player_left.line_length
					+ x * (game->player_left.bits_per_pixel / 8));
			*(unsigned int *)dst = *(unsigned int *)src;
			x++;
		}
		y++;
	}
}

static void	get_image_addr(t_game *game)
{
	game->floor.addr = mlx_get_data_addr(game->floor.img,
			&game->floor.bits_per_pixel,
			&game->floor.line_length, &game->floor.endian);
	game->wall.addr = mlx_get_data_addr(game->wall.img,
			&game->wall.bits_per_pixel,
			&game->wall.line_length, &game->wall.endian);
	game->player.addr = mlx_get_data_addr(game->player.img,
			&game->player.bits_per_pixel,
			&game->player.line_length, &game->player.endian);
	game->collect.addr = mlx_get_data_addr(game->collect.img,
			&game->collect.bits_per_pixel,
			&game->collect.line_length, &game->collect.endian);
	game->exit.addr = mlx_get_data_addr(game->exit.img,
			&game->exit.bits_per_pixel,
			&game->exit.line_length, &game->exit.endian);
}

static int	check_texture_files(void)
{
	if (access("./textures/mandatory/floor.xpm", F_OK) == -1)
	{
		ft_putstr_fd("Error\nNo se encuentra ./textures/mandatory/floor.xpm\n", 2);
		return (0);
	}
	if (access("./textures/mandatory/wall.xpm", F_OK) == -1)
	{
		ft_putstr_fd("Error\nNo se encuentra ./textures/mandatory/wall.xpm\n", 2);
		return (0);
	}
	if (access("./textures/mandatory/player/player.xpm", F_OK) == -1)
	{
		ft_putstr_fd("Error\nNo se encuentra ./textures/mandatory/player/player.xpm\n", 2);
		return (0);
	}
	if (access("./textures/mandatory/collect/collect.xpm", F_OK) == -1)
	{
		ft_putstr_fd("Error\nNo se encuentra ./textures/mandatory/collect/collect.xpm\n", 2);
		return (0);
	}
	if (access("./textures/mandatory/door/exit.xpm", F_OK) == -1)
	{
		ft_putstr_fd("Error\nNo se encuentra ./textures/mandatory/door/exit.xpm\n", 2);
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	int	width;
	int	height;

	if (!check_texture_files())
		return (0);

	init_img(&game->floor);
	init_img(&game->wall);
	init_img(&game->player);
	init_img(&game->player_left);
	init_img(&game->collect);
	init_img(&game->exit);
	init_img(&game->buffer);

	game->buffer.img = mlx_new_image(game->mlx,
			game->map_width * TILE_SIZE,
			game->map_height * TILE_SIZE);
	if (!game->buffer.img)
		return (0);
	game->buffer.addr = mlx_get_data_addr(game->buffer.img,
			&game->buffer.bits_per_pixel,
			&game->buffer.line_length, &game->buffer.endian);
	game->buffer.width = game->map_width * TILE_SIZE;
	game->buffer.height = game->map_height * TILE_SIZE;

	ft_putstr_fd("Iniciando carga de texturas...\n", 1);
	game->floor.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/mandatory/floor.xpm", &width, &height);
	game->wall.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/mandatory/wall.xpm", &width, &height);
	ft_putstr_fd("Cargando textura del jugador...\n", 1);
	game->player.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/mandatory/player/player.xpm", &width, &height);
	if (!game->player.img)
	{
		ft_putstr_fd("Error\nNo se pudo cargar la textura del jugador\n", 2);
		return (0);
	}
	game->player.addr = mlx_get_data_addr(game->player.img,
			&game->player.bits_per_pixel,
			&game->player.line_length, &game->player.endian);
	create_mirrored_player(game, width, height);
	game->collect.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/mandatory/collect/collect.xpm", &width, &height);
	game->exit.img = mlx_xpm_file_to_image(game->mlx,
			"./textures/mandatory/door/exit.xpm", &width, &height);

	if (!game->floor.img || !game->wall.img || !game->player.img ||
		!game->player_left.img || !game->collect.img || !game->exit.img)
	{
		ft_putstr_fd("Error\nNo se pudieron cargar todas las texturas\n", 2);
		return (0);
	}

	get_image_addr(game);
	ft_putstr_fd("Todas las texturas cargadas correctamente\n", 1);
	return (1);
}
