/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_enemy_textures_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	cleanup_loaded_textures(t_game *game, int loaded_count)
{
	int	i;

	i = 0;
	while (i < loaded_count)
	{
		if (game->enemy[i].img)
			mlx_destroy_image(game->mlx, game->enemy[i].img);
		game->enemy[i].img = NULL;
		i++;
	}
}

static int	load_enemy_texture(t_game *game, int index, const char *path)
{
	ft_putstr_fd("Intentando cargar textura de enemigo: ", 1);
	ft_putstr_fd((char *)path, 1);
	ft_putstr_fd("\n", 1);

	game->enemy[index].img = mlx_xpm_file_to_image(game->mlx,
			(char *)path,
			&game->enemy[index].width,
			&game->enemy[index].height);
	if (!game->enemy[index].img)
	{
		ft_putstr_fd("Error: No se pudo cargar la textura del enemigo: ", 1);
		ft_putstr_fd((char *)path, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}

	game->enemy[index].addr = mlx_get_data_addr(game->enemy[index].img,
			&game->enemy[index].bits_per_pixel,
			&game->enemy[index].line_length,
			&game->enemy[index].endian);
	if (!game->enemy[index].addr)
	{
		ft_putstr_fd("Error: No se pudo obtener la dirección de datos del enemigo\n", 1);
		mlx_destroy_image(game->mlx, game->enemy[index].img);
		game->enemy[index].img = NULL;
		return (0);
	}

	ft_putstr_fd("Textura de enemigo cargada con éxito: ", 1);
	ft_putstr_fd((char *)path, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}

int	load_enemy_textures(t_game *game)
{
	const char	*enemy_paths[] = {
		"./textures/bonus/enemy/enemy1.xpm",
		"./textures/bonus/enemy/enemy2.xpm",
		"./textures/bonus/enemy/enemy3.xpm"
	};
	int			i;

	ft_putstr_fd("\n=== Cargando texturas de enemigos ===\n", 1);
	ft_putstr_fd("Número de enemigos en el mapa: ", 1);
	ft_putnbr_fd(game->num_enemies, 1);
	ft_putstr_fd("\n", 1);

	if (game->num_enemies == 0)
	{
		ft_putstr_fd("No hay enemigos en el mapa, omitiendo carga de texturas\n", 1);
		return (1);
	}

	i = 0;
	while (i < ANIMATION_FRAMES)
	{
		if (!load_enemy_texture(game, i, enemy_paths[i % 3]))
		{
			cleanup_loaded_textures(game, i);
			return (0);
		}
		i++;
	}

	ft_putstr_fd("=== Texturas de enemigos cargadas con éxito ===\n\n", 1);
	return (1);
} 