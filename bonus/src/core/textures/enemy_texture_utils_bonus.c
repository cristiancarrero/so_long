/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_texture_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrero <ccarrero@student.42.fr>          +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by ccarrero          #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by ccarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	init_enemy_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

static int	load_enemy_image(t_game *game, t_img *img, char *path)
{
	int	width;
	int	height;

	init_enemy_img(img);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
	{
		ft_putstr_fd("Error: No se pudo cargar la imagen: ", 2);
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

int	create_enemy_image(t_game *game, int frame, char *path)
{
	if (!path)
	{
		ft_putstr_fd("Error: No se pudo generar la ruta del enemigo\n", 2);
		return (0);
	}
	if (!load_enemy_image(game, &game->enemy[frame], path))
	{
		free(path);
		return (0);
	}
	free(path);
	return (1);
}
