/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player_textures_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_player_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

static int	load_player_image(t_game *game, t_img *img, char *path)
{
	int	width;
	int	height;

	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
	{
		ft_putstr_fd("Error: No se pudo cargar la textura: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(game->mlx, img->img);
		img->img = NULL;
		return (0);
	}
	return (1);
}

static int	init_player_right(t_game *game)
{
	char	*path;

	ft_putstr_fd("Intentando cargar textura del jugador derecha...\n", 1);
	path = "./textures/bonus/player/player.xpm";
	ft_putstr_fd("Ruta del jugador: ", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	init_player_img(&game->player);
	if (!load_player_image(game, &game->player, path))
		return (0);
	ft_putstr_fd("Textura del jugador derecha cargada con éxito\n", 1);
	return (1);
}

static int	init_player_left(t_game *game)
{
	char	*path;

	ft_putstr_fd("Intentando cargar textura del jugador izquierda...\n", 1);
	path = "./textures/bonus/player/player.xpm";
	ft_putstr_fd("Ruta del jugador: ", 1);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	init_player_img(&game->player_left);
	if (!load_player_image(game, &game->player_left, path))
		return (0);
	ft_putstr_fd("Textura del jugador izquierda cargada con éxito\n", 1);
	return (1);
}

int	load_player_textures(t_game *game)
{
	ft_putstr_fd("\n=== Cargando texturas del jugador ===\n", 1);
	if (!init_player_right(game))
		return (0);
	if (!init_player_left(game))
	{
		if (game->player.img)
			mlx_destroy_image(game->mlx, game->player.img);
		return (0);
	}
	ft_putstr_fd("=== Texturas del jugador cargadas con éxito ===\n\n", 1);
	return (1);
}
