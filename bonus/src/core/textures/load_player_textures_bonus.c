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

static int	load_player_right(t_game *game)
{
	const char	*player_path;

	ft_putstr_fd("Intentando cargar textura del jugador derecha...\n", 1);
	player_path = "./textures/bonus/player/player.xpm";
	ft_putstr_fd("Ruta del jugador: ", 1);
	ft_putstr_fd((char *)player_path, 1);
	ft_putstr_fd("\n", 1);
	game->player.img = mlx_xpm_file_to_image(game->mlx,
			(char *)player_path,
			&game->player.width,
			&game->player.height);
	if (!game->player.img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen del jugador\n", 1);
		return (0);
	}
	game->player.addr = mlx_get_data_addr(game->player.img,
			&game->player.bits_per_pixel,
			&game->player.line_length,
			&game->player.endian);
	if (!game->player.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos del jugador\n", 1);
		return (0);
	}
	ft_putstr_fd("Textura del jugador derecha cargada con éxito\n", 1);
	return (1);
}

static int	load_player_left(t_game *game)
{
	const char	*player_path;

	ft_putstr_fd("Intentando cargar textura del jugador izquierda...\n", 1);
	player_path = "./textures/bonus/player/player.xpm";
	ft_putstr_fd("Ruta del jugador: ", 1);
	ft_putstr_fd((char *)player_path, 1);
	ft_putstr_fd("\n", 1);
	game->player_left.img = mlx_xpm_file_to_image(game->mlx,
			(char *)player_path,
			&game->player_left.width,
			&game->player_left.height);
	if (!game->player_left.img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen del jugador izquierda\n", 1);
		return (0);
	}
	game->player_left.addr = mlx_get_data_addr(game->player_left.img,
			&game->player_left.bits_per_pixel,
			&game->player_left.line_length,
			&game->player_left.endian);
	if (!game->player_left.addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos del jugador izquierda\n", 1);
		return (0);
	}
	ft_putstr_fd("Textura del jugador izquierda cargada con éxito\n", 1);
	return (1);
}

int	load_player_textures(t_game *game)
{
	ft_putstr_fd("\n=== Cargando texturas del jugador ===\n", 1);
	if (!load_player_right(game))
	{
		ft_putstr_fd("Error al cargar la textura del jugador derecha\n", 1);
		return (0);
	}
	if (!load_player_left(game))
	{
		ft_putstr_fd("Error al cargar la textura del jugador izquierda\n", 1);
		return (0);
	}
	ft_putstr_fd("=== Texturas del jugador cargadas con éxito ===\n\n", 1);
	return (1);
}
